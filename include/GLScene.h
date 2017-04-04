#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h> // Header File For Windows
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <time.h>

#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include <vector>

#include "collider.h"

using namespace std;
class GLScene
{

    public:
        GLScene();
        virtual ~GLScene();
        GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
        GLint InitGL();
        GLint DrawGLScene();

       int  WindowMsg(  HWND,		// Handle For This Window
                        UINT,		// Message For This Window
						WPARAM,		// Additional Message Information
						LPARAM);


        double RotateX;
        double RotateY;
        double RotateZ;
        double Zoom;
        double TranslateX;
        double TranslateY;

        float ScreenHeight;
        float ScreenWidth;

		std::vector< Collider > mColliders;

    protected:

    private:

};

#endif // GLSCENE_H
