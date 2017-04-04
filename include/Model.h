#ifndef MODEL_H
#define MODEL_H

#include <windows.h> // Header File For Windows
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <GL/glut.h>

#include <iostream>

class Model
{
    public:
        Model();
        virtual ~Model();
        void DrawModel();
        void ModelInit(char*);

        double RotateX;
        double RotateY;
        double RotateZ;
        double Zoom;
        double TranslateX;
        double TranslateY;

    protected:

    private:
};

#endif // MODEL_H
