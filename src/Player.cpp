#include "Player.h"
#include "Timer.h"
#include <windows.h>
#include <mmsystem.h>

Timer *T = new Timer();
float t = 0;

#define NUMRUNFRAMES 10
#define NUMSTANDFRAMES 10
#define NUMJUMPFRAMES 10
#define NUMFALLFRAMES 5
#define NUMSLIDEFRAMES 10
#define NUMDEADFRAMES 10

TextureLoader RunTex[NUMRUNFRAMES];
TextureLoader StandTex[NUMSTANDFRAMES];
TextureLoader JumpTex[NUMJUMPFRAMES];
TextureLoader FallTex[NUMFALLFRAMES];
TextureLoader DeadTex[NUMDEADFRAMES];
TextureLoader SlideTex[NUMSLIDEFRAMES];



Player::Player(float size)
{
	mSize = size;
	Reset();
}

Player::~Player()
{
	//dtor
}

void Player::Reset()
{
	mRunFrame = 0;
	mJumpFrame = 0;
	mFallFrame = 0;
	mDieFrame = 0;
	mDead = false;

	mX = 0.0;
	mY = 0.0;

	mState = Standing;
	mDirection = None;


}

void Player::Init()
{
	T->Start();

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	for( int i = 0; i < NUMSTANDFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/templerun/idle" << i << ".png";

		StandTex[i].BindTexture( ss.str().c_str() );
	}

	mCurrentTex = &StandTex[0];

	for( int i = 0; i < NUMDEADFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/templerun/dead" << i << ".png";

		DeadTex[i].BindTexture( ss.str().c_str() );
	}
	for( int i = 0; i < NUMSLIDEFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/templerun/slide" << i << ".png";

		SlideTex[i].BindTexture( ss.str().c_str() );
	}

	for( int i = 0; i < NUMJUMPFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/templerun/jump" << i << ".png";

		JumpTex[i].BindTexture( ss.str().c_str() );
	}

	for( int i = 0; i < NUMRUNFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/templerun/run" << i << ".png";

		RunTex[i].BindTexture( ss.str().c_str() );
	}

	for( int i = 0; i < NUMFALLFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/templerun/fall" << i << ".png";

		FallTex[i].BindTexture( ss.str().c_str() );
	}
}

void Player::drawPlayer()
{

	float width = mCurrentTex->width * mSize;
	float height = mCurrentTex->height * mSize;
	float z = 0;
	glTranslatef( -width / 2, 0, 0.0 );

	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( 0, 0, z );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( width, 0, z );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( width, height, z );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( 0, height, z );
	glEnd();
}



void Player::Render()
{
	glPushMatrix();

	glTranslated( mX, mY, -2.0 );

	switch( mState )
	{

	case Standing:
	mCurrentTex = &StandTex[0];
	break;

	case Running:
	if( T->GetTicks() > 50 )
	{
		mRunFrame++;
		T->Reset();
	}
	mRunFrame = mRunFrame % NUMRUNFRAMES;

	mCurrentTex = &RunTex[mRunFrame];
	break;

	case Sliding:
	if( T->GetTicks() > 80 )
	{
		mRunFrame++;
		T->Reset();
	}
	mRunFrame %= NUMSLIDEFRAMES;
	mCurrentTex = &SlideTex[mRunFrame];
	break;


	case Jumping:
	{
		float jumpstate = ( mY - mGroundHeight ) / ( mJumpHeight );
		mJumpFrame = (int)( jumpstate * (float)NUMJUMPFRAMES ) % ( NUMJUMPFRAMES + 1 );
		mCurrentTex = &JumpTex[mJumpFrame];
		break;
	}
	case Falling:
	{
		if( T->GetTicks() > 100 )
		{
			mFallFrame++;
			T->Reset();
		}
		if( mFallFrame >= NUMFALLFRAMES ) mFallFrame = NUMFALLFRAMES - 1;
		mCurrentTex = &FallTex[mFallFrame];
		break;
	}
	case Dying:
	{
		if( T->GetTicks() > 200 )
		{
			mDieFrame++;
			T->Reset();
		}

		if( mDieFrame >= NUMDEADFRAMES )
		{
			mDead = true;
			mDieFrame = NUMDEADFRAMES - 1;
		}

		mCurrentTex = &DeadTex[mDieFrame];
	}
	}

	mCurrentTex->Bind();

	drawPlayer();
	glPopMatrix();
}

void Player::StartMove( Direction d )
{
	if( mState == Standing )
	{
		mState = Running;
	}
	mDirection = d;
}

void Player::Slide()
{
	if( mState == Running )
		mState = Sliding;
}

void Player::StopSliding()
{
	if( mState == Sliding )
		mState = Running;
}
void Player::Revive(){
    mDead = false;
    mState = Standing;
    mDieFrame = 0;
    mY = mGroundHeight;
}

void Player::Stop()
{
	if( mState == Running || mState == Sliding )
	{
		mState = Standing;
	}
	mDirection = None;
}

void Player::Jump()
{
	if( mState == Running || mState == Standing )
	{
		mState = Jumping;
		PlaySound( "sounds/jump.wav", NULL, SND_ASYNC );
	}
}

void Player::Die()
{
	mState = Dying;
}

void Player::Update( float dt, float height )
{
	if( mState == Dying )
		return;

	mGroundHeight = height * 0.24f;
	mJumpHeight = mGroundHeight + height * 0.4f;

	if( mDirection != None )
	{
		const float speed = 450;
		if( mDirection == Right )
			mX += speed * dt;
		else mX -= speed * dt;
	}

	const float jumpspeed = 500;
	if( mState == Jumping )
	{
		mY += jumpspeed * dt;
		if( mY > mJumpHeight )
		{
			mState = Falling;
		}
	}
	else if( mState == Falling )
	{
		mY -= jumpspeed * dt;
		if( mY < mGroundHeight )
		{
			mY = mGroundHeight;
			if( mDirection == None )
				mState = Standing;
			else mState = Running;
		}
	}
}
