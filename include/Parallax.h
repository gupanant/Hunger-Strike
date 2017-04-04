#ifndef PARALLAX_H
#define PARALLAX_H

#include <windows.h>
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <string.h>
#include <iostream>
using namespace std;


class Parallax
{
    public:
        Parallax();
        virtual ~Parallax();
        void DrawSquare(float, float);//Square wall
        void PrlxInit(char *);              //Initialize texture bind etc.
        void scroll(bool,string,float);      //automatic scrolling, direction
       
		float mX;
		float mY;

		void scrollTo( float x, float y );
    protected:

    private:
};

#endif // PARALLAX_H
