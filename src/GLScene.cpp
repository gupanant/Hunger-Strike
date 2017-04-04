
#include "GLScene.h"
#include "GLLight.h"
#include "Inputs.h"
#include "Model.h"
#include "Parallax.h"
#include "Sprite.h"
#include "Player.h"


Inputs *KbMs = new Inputs();
Model *Mdl = new Model();
Parallax *Prlx = new Parallax();
//Sprite *player = new Sprite();
Player *ply = new Player();

TextureLoader MangoTex;
TextureLoader BombTex;
int scorecount=0;

void makedelay( int a )
{
	glutTimerFunc( 400, makedelay, 0 );
}

//Generating random number
float Random()
{
	return (float)rand() / (float)RAND_MAX;
}



GLScene::GLScene()
{
	ScreenWidth = GetSystemMetrics( SM_CXSCREEN );
	ScreenHeight = GetSystemMetrics( SM_CYSCREEN );

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

	MangoTex.BindTexture( "images/apple.png" );
	BombTex.BindTexture( "images/bomb.png" );

	mColliders.clear();

}

int GLScene::WindowMsg( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )									// Check For Windows Messages
	{
	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		KbMs->wParam = wParam;
		KbMs->KeyEnv( Prlx, 0.008 );
		KbMs->KeyPressed( ply );
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		KbMs->wParam = wParam;
		KbMs->KeyUp( ply );
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

GLint GLScene::InitGL()									// All Setup For OpenGL Goes Here
{
	glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
	glClearDepth( 1.0f );									// Depth Buffer Setup
	glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
	glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

	GLLight Light( GL_LIGHT0 );

	Prlx->PrlxInit( "images/p3.png" );

	ply->playerInit();
	//ply->Player_size[0]=1.2;
	//ply->Player_size[1]=1.2;
	return TRUE;										// Initialization Went OK
}

GLint GLScene::DrawGLScene()							// Here's Where We Do All The Drawing
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix


	// From player.cpp loop on updating step
	static int ticks = 0;
	static int lastclock = clock();
	ticks += clock() - lastclock;
	if( ticks > 15 )
	{
		// Update player position based on inputs.
		ply->Update();

		std::vector< Collider >::iterator i;
		for( i = mColliders.begin(); i != mColliders.end(); ++i )
		{
			i->Update( 0.015 );
			//updating x position
		}

		ticks -= 15;
	}

	static float lastx = 0.0f;
	while( ply->mX + 10.0f > lastx )
	{
	    //putting objects bomb and mango at random places
		lastx = lastx + Random();
		TextureLoader* tex = ( Random() > 0.9f ) ? &BombTex : &MangoTex;
		mColliders.push_back( Collider( lastx, - 0.6f + Random(),
			0.15f + Random()*0.1f, 0.1f + Random() * 0.35f, tex ) );
	}

	glPushMatrix();
	glScalef( 2.0, 2.0, 1.0 );
	Prlx->scrollTo( ply->mX / 8.0f, 0.0f ); // Set parallax position based on players.
	Prlx->DrawSquare( ScreenWidth, ScreenHeight );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW_MATRIX );
	glPushMatrix();
	glTranslatef( -ply->mX, 0.0f, 0.0f );

	ply->Render();

	bool exit = false;

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

				//Need to see how to create new scene or screen here stating game over.
				exit = true;
			}
			// remove mango after collision
			i = mColliders.erase( i );
			scorecount++;
		}
		else i++;
	}

	glPopMatrix();


	return !exit;
}

