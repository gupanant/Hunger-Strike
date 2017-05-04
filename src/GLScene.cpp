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
Parallax *GameOverScreen = new Parallax();
Parallax *GameBG = new Parallax();
//Sprite *player = new Sprite();
Player *ply = new Player();
sound *snds = new sound();

TextureLoader MangoTex;
TextureLoader BombTex;
TextureLoader Volcano;
TextureLoader FireBall;
TextureLoader Orange;

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
void drawText( const char *text, int length, int x, int y )
{
	glMatrixMode( GL_PROJECTION ); // change the current matrix to PROJECTION
	double matrix[16]; // 16 doubles in stack memory
	glGetDoublev( GL_PROJECTION_MATRIX, matrix ); // get the values from PROJECTION matrix to local variable
	glLoadIdentity(); // reset PROJECTION matrix to identity matrix
	glOrtho( 0, 800, 0, 600, -5, 5 ); // orthographic perspective
	glMatrixMode( GL_MODELVIEW ); // change current matrix to MODELVIEW matrix again
	glLoadIdentity(); // reset it to identity matrix
	glPushMatrix(); // push current state of MODELVIEW matrix to stack
	glLoadIdentity(); // reset it again. (may not be required, but it my convention)
	glRasterPos2i( x, y ); // raster position in 2D
	for( int i = 0; i < length; i++ )
	{
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, (int)text[i] ); // generation of characters in our text with 9 by 15 GLU font
	}
	glPopMatrix(); // get MODELVIEW matrix value from stack
	glMatrixMode( GL_PROJECTION ); // change current matrix mode to PROJECTION
	glLoadMatrixd( matrix ); // reset
	glMatrixMode( GL_MODELVIEW ); // change current matrix mode to MODELVIEW
}
//Draw Text Ends

GLScene::GLScene()
{
	ScreenWidth = GetSystemMetrics( SM_CXSCREEN );
	ScreenHeight = GetSystemMetrics( SM_CYSCREEN );

	mState = STATE_TITLE;
	mRunning = true;

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
	gluPerspective( 45.0, aspectRatio, 0.1, 100.0 );

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

void GLScene::OnKeyUp( WPARAM vkkey )
{
	if( mState == STATE_TITLE )
	{
		if( vkkey == VK_RETURN )
		{
			mState = STATE_MENU;
		}
	}
	else if( mState == STATE_MENU )
	{
		if( vkkey == 'N' )
		{
			ResetGameState();
			mState = STATE_INGAME;
		}
		else if( vkkey == 'H' )
		{
			mState = STATE_HELP;
		}
		else if( vkkey == 'E' )
		{
			mState = STATE_EXIT;
		}
	}
	else if( mState == STATE_HELP )
	{
		if( vkkey == 'B' )
		{
			mState = STATE_MENU;
		}
	}
	else if( mState == STATE_EXIT )
	{
		if( vkkey == 'Y' )
		{
			mRunning = false;
		}
		else if( vkkey == 'N' )
		{
			mState = STATE_MENU;
		}
	}
	else if( mState == STATE_GAMEOVER )
	{
		if( vkkey == VK_RETURN )
		{
			mState = STATE_MENU;
			//mRunning = false;
		}
	}
}

void GLScene::ResetGameState()
{
	mScore = 0;
	mLifes = 3;
	mColliders.clear();
}

GLint GLScene::InitGL()									// All Setup For OpenGL Goes Here
{
	glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
	glClearDepth( 1.0f );									// Depth Buffer Setup
	glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
	glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

	GLLight Light( GL_LIGHT0 );
	GameBG->Init( "images/p3.png" );
	GameOverScreen->Init( "images/screen_gameover.png" );
	TitleScreen->Init( "images/screen_title.png" );
	ExitScreen->Init( "images/screen_exit.png" );
	HelpScreen->Init( "images/screen_help.png" );
	MenuScreen->Init( "images/screen_menu.png" );

	MangoTex.BindTexture( "images/apple.png" );
	BombTex.BindTexture( "images/bomb.png" );
	FireBall.BindTexture( "images/fireball.png" );
	Volcano.BindTexture( "images/volcano.png" );
	Orange.BindTexture( "images/orange.png" );
	ply->playerInit();
	snds->soundinit();
	snds->playMusic( "sounds/MF-W-90.XM" );
	//ply->Player_size[0]=1.2;
	//ply->Player_size[1]=1.2;
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


	return mRunning;
}

void GLScene::DrawIngame()
{
	GameBG->scrollTo( ply->mX / 8.0f, 0.0f ); // Set parallax position based on players.
	GameBG->DrawSquare( ScreenWidth, ScreenHeight );

	// From player.cpp loop on updating step
	static int ticks = 0;
	static int lastclock = clock();
	ticks += clock() - lastclock;
	if( ticks > 35 )
	{
		// Update player position based on inputs.
		ply->Update();

		std::vector< Collider >::iterator i;
		for( i = mColliders.begin(); i != mColliders.end(); ++i )
		{
			i->Update( 0.015 );
			//updating x position
		}
		ticks -= 35;
	}

	static float lastx = 0.0f;
	if( ticks > 35 )
	{
		while( ply->mX + 5.0f > lastx )
		{
			//putting objects bomb and mango at random places
			lastx = lastx + Random();
			TextureLoader* tex = ( Random() > 0.9f ) ? &BombTex : &MangoTex;
			mColliders.push_back( Collider( lastx, -0.6f + Random(), 0.15f + Random()*0.1f, 0.1f + Random() * 0.35f, tex ) );

		}
	}
	/*else
	{
		while( ply->mX + 5.0f > lastx )
		{
			lastx = lastx + Random();
			TextureLoader* tex1 = ( Random() > 0.9f ) ? &FireBall : &Orange;
			mColliders.push_back( Collider( lastx, -0.6f + Random(), 0.15f + Random()*0.1f, 0.1f + Random() * 0.35f, tex1 ) );
		}
	}*/

	//Updating Score
	gluLookAt( 0, 0, -10, 0, 0, 3, 0, 1, 0 );
	glBegin( GL_LINES );
	glVertex3f( 0, 0, 0 );
	glVertex3f( 1, 0, 0 );
	glEnd();
	std::string text;
	text = "Your Score : ";
	std::stringstream ss;
	ss << mScore;
	std::string pika = text + ss.str();
	drawText( pika.data(), pika.size(), 10, 580 );
	//Updating Score ends

	//Updating Score
	gluLookAt( 0, 0, -10, 0, 0, 3, 0, 1, 0 );
	glBegin( GL_LINES );
	glVertex3f( 0, 0, 0 );
	glVertex3f( 1, 0, 0 );
	glEnd();
	std::string text2;
	text2 = "LIFES REMAINING:";
	std::stringstream ss2;
	ss2 << mLifes;
	std::string pika2 = text2 + ss2.str();
	drawText( pika2.data(), pika2.size(), 700, 580 );
	//Updating Score ends

	glMatrixMode( GL_MODELVIEW_MATRIX );
	glPushMatrix();
	glTranslatef( -ply->mX, 0.0f, 0.0f );

	ply->Render();



	// Loop over all collisions.
	std::vector< Collider >::iterator i;
	for( i = mColliders.begin(); i != mColliders.end(); )
	{
		i->Render();

		// Check if it collides with player.
		if( i->Collides( ply->mX + 0.18f, ply->mY - 0.1f, 0.1f ) )
		{
			if( i->mTex == &BombTex )
			{
				mLifes--;
				snds->playSound( "sounds/explosion.wav" );
				if( mLifes <= 0 )
				{
					mState = STATE_GAMEOVER;
				}

			}
			// remove mango after collision
			i = mColliders.erase( i );
			mScore++;
		}
		else i++;
	}

	glPopMatrix();

}

void GLScene::DrawTitleScreen()
{
	TitleScreen->DrawSquare( ScreenWidth , ScreenHeight );
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

