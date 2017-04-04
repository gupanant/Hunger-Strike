#include <Sprite.h>
#include <TextureLoader.h>
#include <windows.h> // Header File For Windows
#include <gl/gl.h>

#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream> 		// Header File For The GLu32 Library
#include <string>

#include <Timer.h>

using namespace std;

TextureLoader *Stex = new TextureLoader();



Sprite::Sprite()
{

}

Sprite::~Sprite()
{
    //dtor
}

void Sprite::SpriteInit(char *fileName)
{

}

void Sprite::Action(int action)
{

}

void Sprite::draw_sprite()
{
  glScaled(sprit_size[0],sprit_size[1],sprit_size[2]);
  glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(Vertices[0][0],Vertices[0][1],Vertices[0][2]);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(Vertices[1][0],Vertices[1][1],Vertices[1][2]);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(Vertices[2][0],Vertices[2][1],Vertices[2][2]);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(Vertices[3][0],Vertices[3][1],Vertices[3][2]);
  glEnd();
}




