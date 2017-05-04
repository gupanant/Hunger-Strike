#include "Player.h"
#include "Timer.h"
#include <windows.h>
#include <mmsystem.h>

Timer *T = new Timer();
float t = 0;

#define NUMRUNFRAMES 23
#define NUMSTANDFRAMES 1
#define NUMJUMPFRAMES 8
#define NUMFALLFRAMES 6

TextureLoader runTtex[NUMRUNFRAMES];
TextureLoader stndTtex[NUMSTANDFRAMES];
TextureLoader jumpTtex[NUMJUMPFRAMES];
TextureLoader fallTtex[NUMFALLFRAMES];



Player::Player()
{
	//ctor
	mRunFrame = 0;
	mJumpFrame = 0;
	mFallFrame = 0;

}

Player::~Player()
{
	//dtor
}

void Player::playerInit()
{
	T->Start();

	mX = 0.0;
	mY = 0.0;

	mState = Standing;
	mDirection = None;

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	stndTtex[0].BindTexture( "images/player/playeridle0.png" );

	for( int i = 0; i < NUMJUMPFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/player/playerjump" << i << ".png";

		jumpTtex[i].BindTexture( ss.str().c_str() );
	}

	for( int i = 0; i < NUMRUNFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/player/player" << i << ".png";

		runTtex[i].BindTexture( ss.str().c_str() );
	}

	for( int i = 0; i < NUMFALLFRAMES; ++i )
	{
		std::stringstream ss;
		ss << "images/player/playerfall" << i << ".png";

		fallTtex[i].BindTexture( ss.str().c_str() );
	}
}

void Player::drawPlayer()
{
	glTranslatef( -0.5f, -1.0f, 0.0 );
	glScaled( Player_size[0], Player_size[1], Player_size[2] );

	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( Vertices[0][0], Vertices[0][1], Vertices[0][2] );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( Vertices[1][0], Vertices[1][1], Vertices[1][2] );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( Vertices[2][0], Vertices[2][1], Vertices[2][2] );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( Vertices[3][0], Vertices[3][1], Vertices[3][2] );
	glEnd();
}

const float GroundHeight = 0.0f;
const float JumpHeight = 1.2f;

void Player::Render()
{
	glPushMatrix();

	glTranslated( mX, mY, -2.0 );

	switch( mState )
	{

	case Standing:
		stndTtex[0].Bind();
		break;

	case Running:
		if( T->GetTicks() > 15 )
		{
			mRunFrame++;
			T->Reset();
		}
		mRunFrame = mRunFrame % NUMRUNFRAMES;

		runTtex[mRunFrame].Bind();

		break;


	case Jumping:
	{
		float jumpstate = ( mY - GroundHeight ) / ( JumpHeight );
		mJumpFrame = (int)( jumpstate * (float)NUMJUMPFRAMES ) % (NUMJUMPFRAMES + 1);
		jumpTtex[mJumpFrame].Bind();
		break;
	}
	case Falling:
	{
		if( T->GetTicks() > 30 )
		{
			mFallFrame++;
			T->Reset();
		}
		if( mFallFrame >= NUMFALLFRAMES ) mFallFrame = NUMFALLFRAMES - 1;
		fallTtex[mFallFrame].Bind();
		break;
	}
	}

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

void Player::Stop()
{
	if( mState == Running )
	{
		mState = Standing;
	}
	mDirection = None;
}

void Player::Jump()
{
	if( mState == Running || mState == Standing )
		mState = Jumping;
    PlaySound("jump.wav", NULL, SND_ASYNC);
}

void Player::Update()
{

	if( mDirection != None )
	{
		const float speed = 0.004f;
		if( mDirection == Right )
			mX += speed;
		else mX -= speed;
	}

	const float jumpspeed = 0.004f;
	if( mState == Jumping )
	{
		mY += jumpspeed;
		if( mY > JumpHeight )
		{
			mState = Falling;
		}
	}
	else if( mState == Falling )
	{
		mY -= jumpspeed;
		if( mY < GroundHeight )
		{
			mY = GroundHeight;
			if( mDirection == None )
				mState = Standing;
			else mState = Running;
		}
	}
}
