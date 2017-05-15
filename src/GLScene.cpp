#include "GLScene.h"
#include "GLLight.h"
#include "Inputs.h"
#include "Model.h"
#include "Parallax.h"
#include "Sprite.h"
#include "Player.h"
#include <string>
#include <sstream>
#include <sound.h>

Inputs *KbMs = new Inputs();
Model *Mdl = new Model();

Parallax* TitleScreen = new Parallax();
Parallax* MenuScreen = new Parallax();
Parallax* HelpScreen = new Parallax();
Parallax* ExitScreen = new Parallax();
Parallax* GameOverScreen = new Parallax();
Parallax* GameBG = new Parallax();
Parallax* GameBG2 = new Parallax();
Parallax* GameBG3 = new Parallax();
Parallax* UserNameScreen = new Parallax();
Parallax* HighScoreScreen = new Parallax();
Parallax* CreditsScreen = new Parallax();

Player *ply = new Player( 0.3f );
sound *snds = new sound();

TextureLoader MangoTex;
TextureLoader BombTex;
TextureLoader Volcano;
TextureLoader FireBall;
TextureLoader Orange;
TextureLoader Bullet;
TextureLoader WaterMellon;
TextureLoader Papaya;
TextureLoader Cherry;

void makedelay( int a )
{
	glutTimerFunc( 400, makedelay, 0 );
}

//Generating random number
float Random()
{
	return (float)rand() / (float)RAND_MAX;
}

/*Draw Text */
void drawText( const char *text, int length, int x, int y, int colors )
{
    glDisable(GL_LIGHTING);
	glMatrixMode( GL_MODELVIEW ); // change current matrix to MODELVIEW matrix again
	glPushMatrix(); // push current state of MODELVIEW matrix to stack
	glLoadIdentity(); // reset it again. (may not be required, but it my convention)
    if (colors == 1)
    {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    else if (colors==2)
    {
        glColor3f(1.0f, 1.0f, 0.0f);
    }

	glRasterPos2i( x, y ); // raster position in 2D
	for( int i = 0; i < length; i++ )
	{
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i] ); // generation of characters in our text with 9 by 15 GLU font
	}
	glPopMatrix(); // get MODELVIEW matrix value from stack
	glEnable(GL_LIGHTING);
}
//Draw Text Ends

GLScene::GLScene()
{
	ScreenWidth = GetSystemMetrics( SM_CXSCREEN );
	ScreenHeight = GetSystemMetrics( SM_CYSCREEN );

	mState = STATE_TITLE;
	mRunning = true;

	LoadHighScores( HIGHSCOREFILE );
}

GLScene::~GLScene()
{
	//dtor
}


GLvoid GLScene::ReSizeGLScene( GLsizei Width, GLsizei Height )		// Resize And Initialize The GL Window
{

	GLfloat aspectRatio = (GLfloat)Width / (GLfloat)Height;

	ScreenWidth = Width;
	ScreenHeight = Height;

	glViewport( 0, 0, Width, Height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, Width, 0, Height, -100.0, 100.0 );
	//gluPerspective( 45.0, aspectRatio, 0.1, 100.0 );

	glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	mColliders.clear();

}



int GLScene::WindowMsg( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )									// Check For Windows Messages
	{
	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		KbMs->wParam = wParam;
		KbMs->KeyEnv( GameBG, 0.008 );
		KbMs->KeyPressed( ply );
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		KbMs->wParam = wParam;
		KbMs->KeyUp( ply );
		OnKeyUp( wParam );
		return 0;								// Jump Back
	}

	case WM_LBUTTONDOWN:
	{
		KbMs->wParam = wParam;
		OnMouseDown(wParam,LOWORD( lParam ), HIWORD( lParam ));
		KbMs->MouseEventDown( Mdl, LOWORD( lParam ), HIWORD( lParam ) );
		return 0;								// Jump Back
	}

	case WM_RBUTTONDOWN:
	{
		KbMs->wParam = wParam;
		KbMs->MouseEventDown( Mdl, LOWORD( lParam ), HIWORD( lParam ) );
		return 0;								// Jump Back
	}

	case WM_MBUTTONDOWN:
	{
		KbMs->wParam = wParam;
		KbMs->MouseEventDown( Mdl, LOWORD( lParam ), HIWORD( lParam ) );
		return 0;								// Jump Back
	}

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	{
		KbMs->MouseEventUp();
		return 0;								// Jump Back
	}

	case WM_MOUSEMOVE:
	{
		KbMs->MouseMove( Mdl, LOWORD( lParam ), HIWORD( lParam ) );
		return 0;								// Jump Back
	}

	case WM_MOUSEWHEEL:
	{
		KbMs->MouseWheel( Mdl, (double)GET_WHEEL_DELTA_WPARAM( wParam ) );
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		// LoWord=Width, HiWord=Height
		ReSizeGLScene( LOWORD( lParam ), HIWORD( lParam ) );
		return 0;								// Jump Back
	}
	}

	return 1;
}

void GLScene::OnMouseDown(WPARAM vkkey, double x, double y)
{
    float sw = ScreenWidth;
    float sh = ScreenHeight;

    float xn,yn;
    cout<<"x :"<<x<<endl;
    cout<<"y :"<<y<<endl;

    cout<<"resol :"<<sw<<" * "<<sh<<endl;

    if(mState== STATE_TITLE)
    {

        if(xn > -1.23474 && xn < 1.24567 && yn > 1.48333 && yn < 2.01874)
            mState = STATE_MENU;
    }
    else if(mState == STATE_MENU)
    {
        if(xn>-3.49 && xn < -2.31 && yn > -1.51 && yn < -0.298)
        {
            ResetGameState();
			mState = STATE_ASKNAME;
        }
        else if(xn > -1.97438 && xn < -0.86625 && yn > -1.35 && yn < -0.11)
        {
            mState = STATE_HIGHSCORE;
        }
        else if(xn > -0.35437 && xn < 0.65251 && yn > -1.35 && yn < -0.11)
        {
            mState = STATE_CREDITS;
        }
        else if(xn > 1.09125 && xn < 2.115 && yn > -1.35 && yn < -0.11)
        {
            mState = STATE_HELP;
        }
        else if(xn > 2.52 && xn < 3.6225 && yn > -1.35 && yn < -0.11)
        {
            mPreviousState = mState;
            mState = STATE_EXIT;
        }
    }
    else if(mState == STATE_HELP )
    {
        if(xn > -4.07812 && xn < -2.48625 && yn > -2.12625 && yn < -1.60875){
            mState = STATE_MENU;
        }

    }
    else if(mState == STATE_CREDITS)
    {
         if(xn > -4.07812 && xn < -2.48625 && yn > -2.12625 && yn < -1.60875){
            mState = STATE_MENU;
        }
    }
    else if(mState == STATE_EXIT)
    {
        if(xn > -1.215 && xn < 0.63 && yn > -0.579375 && yn < -0.140625)
        {
            mRunning = false;
        }
        else if(xn > -1.18125 && xn < 0.174375 && yn > 0.4725 && yn < 0.95625)
        {
            mState = mPreviousState;
        }

    }
    else if(mState == STATE_HIGHSCORE)
    {
         if(xn > -4.07812 && xn < -2.48625 && yn > -2.12625 && yn < -1.60875){
            mState = STATE_MENU;
         }
    }

}

void GLScene::OnKeyUp( WPARAM vkkey )
{
	if( mState != STATE_EXIT && vkkey == VK_ESCAPE )
	{
		mPreviousState = mState;
		mState = STATE_EXIT;
	}
	else if( mState == STATE_INGAME )
	{
		if( vkkey == VK_SPACE )
			Shoot();
	}
	else if( mState == STATE_TITLE )
	{
		if( vkkey == VK_RETURN )
		{
			mState = STATE_MENU;
		}
	}
	else if( mState == STATE_MENU )
	{
		if( vkkey == 'P' )
		{
			ResetGameState();
			mState = STATE_ASKNAME;
		}
		else if( vkkey == 'H' )
		{
			mState = STATE_HELP;
		}
		else if( vkkey == 'C' )
		{
			mState = STATE_CREDITS;
		}
		else if( vkkey == 'Q' )
		{
			mPreviousState = mState;
			mState = STATE_EXIT;
		}
		else if( vkkey == 'S' )
		{
			mState = STATE_HIGHSCORE;
		}
	}
	else if( mState == STATE_HIGHSCORE )
	{
		if( vkkey == VK_RETURN || vkkey == 'B' )
		{
			mState = STATE_MENU;
		}
	}
    else if( mState == STATE_CREDITS )
	{
		if( vkkey == VK_RETURN || vkkey == 'B' )
		{
			mState = STATE_MENU;
		}
	}
	else if( mState == STATE_HELP )
	{
		if( vkkey == VK_RETURN || vkkey == 'B' )
		{
			mState = STATE_MENU;
		}
	}
	else if( mState == STATE_EXIT )
	{
		if( vkkey == VK_RETURN || vkkey == 'Y' )
		{
			mRunning = false;
		}
		else if( vkkey == 'N' )
		{
			mState = mPreviousState;
		}

	}
	else if( mState == STATE_GAMEOVER )
	{
		if( vkkey == VK_RETURN )
		{
			Score s;
			s.name = mName;
			s.score = mScore;
			AddHighScore( s );
			SaveHighScores( HIGHSCOREFILE );
			mState = STATE_HIGHSCORE;
		}
	}
	else if( mState == STATE_ASKNAME )
	{
		if( vkkey >= 'A' && vkkey <= 'Z' )
		{
			mName.append( 1, (char)vkkey );
		}
		if( vkkey == VK_BACK )
		{
			mName.erase( mName.end() - 1 );
		}
		if( vkkey == VK_RETURN )
		{
			mState = STATE_INGAME;
		}
	}
}

void GLScene::ResetGameState()
{
	mScore = 0;
	mLifes = 3;
	mName = "";
	mColliders.clear();
	mLastx = 0.0f;
	ply->Reset();
	ply->mX = ScreenWidth / 2;
	ply->mY = ScreenHeight * 0.24f;
	mTime = 0;
}

GLint GLScene::InitGL()									// All Setup For OpenGL Goes Here
{
	glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
	glClearDepth( 1.0f );									// Depth Buffer Setup
	glDisable( GL_CULL_FACE );
	glDisable( GL_DEPTH_TEST );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

	GLLight Light( GL_LIGHT0 );
	GameBG->Init( "images/levels/level1.png" );
	GameBG2->Init( "images/levels/level2.png" );
	GameBG3->Init( "images/levels/level3.png" );
	GameOverScreen->Init( "images/screens/screen_gameover.jpg" );
	TitleScreen->Init( "images/screens/screen_title.png" );
	ExitScreen->Init( "images/screens/screen_exit.png" );
	HelpScreen->Init( "images/screens/screen_help.png" );
	MenuScreen->Init( "images/screens/screen_menu.png" );
	UserNameScreen->Init("images/screens/screen_name.jpg");
	HighScoreScreen->Init( "images/screens/screen_highscore.png" );
	CreditsScreen->Init("images/screens/screen_credits.png");

	MangoTex.BindTexture( "images/objects/apple.png" );
	BombTex.BindTexture( "images/objects/bomb.png" );
	FireBall.BindTexture( "images/objects/fireball.png" );
	Volcano.BindTexture( "images/objects/cac.png" );
	Orange.BindTexture( "images/objects/orange.png" );
	Bullet.BindTexture( "images/objects/bullet.png" );
	WaterMellon.BindTexture( "images/objects/watermellon.png" );
	Cherry.BindTexture( "images/objects/cherry.png" );
	Papaya.BindTexture( "images/objects/papaya.png" );
	ply->Init();
	snds->soundinit();
	snds->playMusic( "sounds/game_sound.wav" );
	return TRUE;										// Initialization Went OK
}

GLint GLScene::DrawGLScene()							// Here's Where We Do All The Drawing
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear Screen And Depth Buffer
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	// Reset The Current Modelview Matrix

	if( mState == STATE_INGAME )
	{
		DrawIngame();
	}
	else if( mState == STATE_TITLE )
	{
		DrawTitleScreen();
	}
	else if( mState == STATE_CREDITS )
	{
		DrawCreditsScreen();
	}
	else if( mState == STATE_MENU )
	{
		DrawMenuScreen();
	}
	else if( mState == STATE_HELP )
	{
		DrawHelpScreen();
	}
	else if( mState == STATE_GAMEOVER )
	{
		DrawGameOverScreen();
	}
	else if( mState == STATE_EXIT )
	{
		DrawExitScreen();
	}
	else if( mState == STATE_ASKNAME )
	{
		DrawAskNameScreen();
	}
	else if( mState == STATE_HIGHSCORE )
	{
		DrawHighScoreScreen();
	}

	return mRunning;
}


int aabb_aabb_axes( float aminx, float aminy, float amaxx, float amaxy,
	float bminx, float bminy, float bmaxx, float bmaxy,
	int* x, int* y )
{
	int cx = aminx <= bmaxx && amaxx >= bminx;
	int cy = aminy <= bmaxy && amaxy >= bminy;
	if( x ) *x = cx;
	if( y ) *y = cy;

	return cx && cy;
}

void GLScene::DrawIngame()
{
	Parallax* currentbg = GameBG;

	if( mTime > 80000 ) currentbg = GameBG3;
	else if( mTime > 40000 ) currentbg = GameBG2;

	currentbg->scrollTo( ply->mX / ScreenWidth, 0.0f ); // Set parallax position based on players.
	currentbg->DrawSquare( ScreenWidth, ScreenHeight );



	static int ticks = 0;
	static int lastclock = clock();
	int now = clock();
	int elapsed = now - lastclock;
	ticks += elapsed;
	lastclock = now;
	mTime += elapsed;

	while( ticks > 16 )
	{
      if (!ply -> IsDying()) {
		// Update player position based on inputs.
		ply->Update( 0.016, ScreenHeight );

		// Move colliders and bullets.
		for( std::vector< Collider >::iterator i = mColliders.begin(); i != mColliders.end(); ++i )
		{
			i->Update( 0.016 );
		}
		for( std::vector< Collider >::iterator i = mBullets.begin();i != mBullets.end(); )
		{
			i->Update( 0.016 );

			float aw = i->mTex->width * i->mR * 0.5f;
			float ah = i->mTex->height * i->mR * 0.5f;

			float aminx = i->mX - aw;
			float amaxx = i->mX + aw;
			float aminy = i->mY - ah;
			float amaxy = i->mY + ah;

			bool collision = false;
			for( std::vector< Collider >::iterator j = mColliders.begin();
				j != mColliders.end(); )
			{
				// Check for collision. If collision happens, delete both.

				float bw = j->mTex->width * j->mR * 0.5f;
				float bh = j->mTex->height * j->mR * 0.5f;
				float bminx = j->mX - bw;
				float bmaxx = j->mX + bw;
				float bminy = j->mY - bh;
				float bmaxy = j->mY + bh;
				int c = aabb_aabb_axes( aminx, aminy, amaxx, amaxy,
					bminx, bminy, bmaxx, bmaxy,
					NULL, NULL );

				if( c )
				{
				    snds->playSound( "sounds/explosion.wav" );
					mPS.GenerateExplosion( i->mX, i->mY, 500 );
					j = mColliders.erase( j );
					collision = true;
					break;
				}
				else ++j;

			}

			if( !collision )
				i++;
			else i = mBullets.erase( i );

		}
		while( ply->mX + ScreenWidth * 0.6f > mLastx )
		{
			//putting objects bomb and mango at random places
			mLastx = mLastx + Random() * 100;
		}

		// Spawn a collider every 10 ticks.
		static int counter = 0;
		counter++;
		if( counter > 20 )
		{
			counter -= 20;

			float posx = mLastx;
			float posy = ScreenHeight / 3 + Random() * 300;
			float size = 0.1f + Random() * 0.025f;
			float speed = 200 + Random() * 250;
			TextureLoader* tex = NULL;

			if( currentbg == GameBG ) // Apple, orange, bomb.
			{
				float what = Random();
				if( what > 0.9f )
					tex = &BombTex;
				else if( what > 0.7f )
					tex = &Cherry;
                else if( what > 0.5f )
					tex = &MangoTex;
                else if( what > 0.3f )
					tex = &Papaya;
                else if( what > 0.15f )
					tex = &WaterMellon;
				else tex = &Orange;
			}
			else if( currentbg == GameBG2 ) // fireball, bomb.
			{
				float what = Random();
				if( what > 0.92f )
					tex = &BombTex;
				else if( what > 0.86f )
				{
					tex = &FireBall;
					size /= 2;
				}
				else if( what > 0.76f )
					tex = &Cherry;
                else if( what > 0.66f )
					tex = &MangoTex;
                else if( what > 0.56f )
					tex = &Papaya;
                else if( what > 0.36f )
					tex = &WaterMellon;
				else tex = &Orange;
			}
			else // fireball, bomb, volcano.
			{
				float what = Random();
				if( what > 0.9f )
					tex = &BombTex;
				else if( what > 0.82f )
					tex = &FireBall;
                else if( what > 0.75f )
					tex = &Cherry;
                else if( what > 0.65f )
					tex = &MangoTex;
				else if( what > 0.55f )
				{
					tex = &Volcano;
					speed = 0;
					size *= 4.f;
					posy = ScreenHeight * 0.25f;
				}
                else if( what > 0.25f )
					tex = &Papaya;
                else if( what > 0.15f )
					tex = &WaterMellon;
				else tex = &Orange;
			}

			if( tex == &Orange )
				size *= 2.0f;

			if( tex )
				mColliders.push_back( Collider( posx, posy, size, speed, tex ) );
		}
      }
        mPS.Update( 0.016, ScreenHeight * 0.245f );
		mPS.GenerateRain( ply->mX - ScreenWidth * 0.8f, ScreenWidth * 1.6f, ScreenHeight );
		ticks -= 16;
	}

	//some bug causes first drawtext to draw nothing.
    //so we do a dummy call to fix this.
	drawText( " ", 1, 0, 0, 2 );


	//Updating Score
	std::stringstream ss;
	ss << "Score:" << mScore;
	std::string text = ss.str();
	drawText( text.c_str(), text.length(), 0, ScreenHeight - 20, 1 );
	//Updating Score ends


	//Updating Score

	std::stringstream ss2;
	ss2 << "LIVES:" << mLifes;
	std::string text2 = ss2.str();
	drawText( text2.c_str(), text2.length(),
		ScreenWidth - 15 * text2.length(), ScreenHeight - 20, 1 );
	//Updating Score ends



	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	glTranslatef( -ply->mX + ScreenWidth / 2, 0.0f, 0.0f );

	ply->Render();

	for( std::vector<Collider>::iterator i = mBullets.begin(); i != mBullets.end(); ++i )
	{
		i->Render();
	}

	// Loop over all collisions.
	for( std::vector<Collider>::iterator i = mColliders.begin(); i != mColliders.end(); )
	{
		i->Render();

		float aw = i->mTex->width * i->mR * 0.5f;
		float ah = i->mTex->height * i->mR * 0.5f;

		float aminx = i->mX - aw;
		float amaxx = i->mX + aw;
		float aminy = i->mY - ah;
		float amaxy = i->mY + ah;

		float hw = ply->mCurrentTex->width / 2.f;
		hw *= ply->mSize;
		hw *= 0.8f;
		float bminx = ply->mX - hw;
		float bmaxx = ply->mX + hw;
		float bminy = ply->mY;
		float bmaxy = ply->mY + ply->mCurrentTex->height * ply->mSize * 0.8f;

		int c = aabb_aabb_axes( aminx, aminy, amaxx, amaxy, bminx, bminy, bmaxx, bmaxy,
				NULL, NULL );
		// Check if it collides with player.
		if( c )
		{
			if( i->mTex == &BombTex || i->mTex == &FireBall || i->mTex == &Volcano )
			{
				ply-> Die();
				//mLifes--;
				//ply->Die();
				snds->playSound( "sounds/life-lost.wav" );
				mPS.GenerateExplosion( i->mX, i->mY, 500 );

			}
			else
			{
			    snds->playSound( "sounds/collect.wav" );
				mScore++;
			}

			// remove object after collision.
			i = mColliders.erase( i );
		}
		else i++;
	}

	mPS.drawParticles();

	glPopMatrix();

	if( ply->IsDead() )
	{
	    mLifes--;
	    ply->Revive();
	    ticks=0;
	}
	if (mLifes ==0){
        mState = STATE_GAMEOVER;
	}

}

void GLScene::DrawTitleScreen()
{
	TitleScreen->DrawSquare( ScreenWidth, ScreenHeight );
}

void GLScene::DrawCreditsScreen()
{
	CreditsScreen->DrawSquare( ScreenWidth, ScreenHeight );
}

void GLScene::DrawMenuScreen()
{
	MenuScreen->DrawSquare( ScreenWidth, ScreenHeight );
}

void GLScene::DrawHelpScreen()
{
	HelpScreen->DrawSquare( ScreenWidth, ScreenHeight );
}

void GLScene::DrawGameOverScreen()
{
	GameOverScreen->DrawSquare( ScreenWidth, ScreenHeight );
}

void GLScene::DrawExitScreen()
{
	ExitScreen->DrawSquare( ScreenWidth, ScreenHeight );
}

void GLScene::DrawAskNameScreen()
{
    UserNameScreen->DrawSquare( ScreenWidth, ScreenHeight );
	std::stringstream name;
	name << mName;
	std::string str = name.str();
	drawText( str.c_str(), str.length(), (int)((ScreenWidth / 3) + 20), (int)ScreenHeight / 2, 1 );
}

void GLScene::DrawHighScoreScreen()
{
	HighScoreScreen->DrawSquare( ScreenWidth, ScreenHeight );
	int n = mHighScores.size();
	if( n > 15 ) n = 15;
	for( size_t i = 0; i < n; ++i )
	{
		std::stringstream ss;
		Score s = mHighScores[i];
		ss << ( i + 1 ) << ". " << std::setw( 15 ) << std::setfill( ' ' ) << s.name
			<< "  " << std::setw( 4 ) << std::setfill( '0' ) << s.score;
		std::string scoretext = ss.str();
		drawText( scoretext.c_str(), scoretext.length(),
			(int)ScreenWidth * 0.4f,
			(int)( ScreenHeight * 0.65f ) - i * 25, 2 );
	}
}


void GLScene::SaveHighScores( std::string filename )
{
	std::ofstream file( filename.c_str(), std::ios_base::trunc );
	if( !file.is_open() )
	{
		std::cerr << "Error opening file " << filename << " for writing." << std::endl;
		return;
	}


	file << mHighScores.size() << std::endl;
	size_t size = mHighScores.size();
	if( size > 15 ) size = 15;
	for( size_t i = 0; i < size; ++i )
	{
		Score s = mHighScores[i];
		file << s.name << " " << s.score << std::endl;
	}
}

bool scoresort( const GLScene::Score& a, const GLScene::Score& b )
{
	return a.score > b.score;
}

void GLScene::LoadHighScores( std::string filename )
{
	std::ifstream file( filename.c_str() );
	if( !file.is_open() )
	{
		std::cerr << "Error opening file " << filename << " for reading." << std::endl;
		return;
	}

	size_t nscores;
	file >> nscores;
	for( size_t i = 0; i < nscores; ++i )
	{
		Score s;
		file >> s.name >> s.score;
		mHighScores.push_back( s );
	}

	// Make sure scores are ordered.
	std::sort( mHighScores.begin(), mHighScores.end(), scoresort );
}

void GLScene::AddHighScore( Score s )
{
	mHighScores.push_back( s );
	std::sort( mHighScores.begin(), mHighScores.end(), scoresort );

}

void GLScene::Shoot()
{
    snds->playSound( "sounds/shoot.wav" );
	if( ply->IsDying() ) return;

	mBullets.push_back( Collider( ply->mX,
		ply->mY + ply->mSize * ply->mCurrentTex->height * 0.65f, 0.25f, -600, &Bullet ) );
}
