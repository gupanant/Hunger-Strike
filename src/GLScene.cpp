
#include <GLScene.h>
#include <GLLight.h>
#include <Inputs.h>
#include <Model.h>
#include <Parallax.h>
#include <Sprite.h>
#include <Player.h>


Inputs *KbMs = new Inputs();
Model *Mdl = new Model();
Parallax *Prlx = new Parallax();
//Sprite *player = new Sprite();
Player *ply = new Player();

void makedelay(int a)
{
   glutTimerFunc(400,makedelay,0);
}

GLScene::GLScene()
{
    ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    ScreenHeight= GetSystemMetrics(SM_CYSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}


GLvoid GLScene::ReSizeGLScene(GLsizei Width, GLsizei Height)		// Resize And Initialize The GL Window
{

GLfloat aspectRatio = (GLfloat)Width / (GLfloat)Height;

    ScreenWidth = Width;
    ScreenHeight= Height;

    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();									// Reset The Modelview Matrix
}

int GLScene::WindowMsg(HWND hWnd,UINT uMsg, WPARAM wParam,LPARAM lParam)
{
    switch (uMsg)									// Check For Windows Messages
	{
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
		    KbMs->wParam = wParam;
		    KbMs->KeyEnv(Prlx,0.008);
		    KbMs->KeyPressed(ply);
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			KbMs->wParam = wParam;
			KbMs->KeyUp(ply);
			return 0;								// Jump Back
		}

		case WM_LBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->MouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
            return 0;								// Jump Back
        }

   		case WM_RBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->MouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
            return 0;								// Jump Back
        }

          case WM_MBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->MouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
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
             KbMs->MouseMove(Mdl, LOWORD(lParam),HIWORD(lParam));
             return 0;								// Jump Back
        }

        case WM_MOUSEWHEEL:
        {
            KbMs->MouseWheel(Mdl,(double)GET_WHEEL_DELTA_WPARAM(wParam));
            return 0;								// Jump Back
        }

		case WM_SIZE:								// Resize The OpenGL Window
		{
                                                    // LoWord=Width, HiWord=Height
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
			return 0;								// Jump Back
		}
	}
}

GLint GLScene::InitGL()									// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	GLLight Light(GL_LIGHT0);

	Prlx->PrlxInit("images/p3.png");

	ply->playerInit();
    ply->Player_size[0]=1.2;
	ply->Player_size[1]=1.2;
	return TRUE;										// Initialization Went OK
}

GLint GLScene::DrawGLScene()							// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

    glPushMatrix();
    glScalef(3.33,3.33,1.0);
        Prlx->DrawSquare(ScreenWidth,ScreenHeight);
    glPopMatrix();

    ply->Action(ply->actionTrigger);

  	return TRUE;										// Keep Going
}

