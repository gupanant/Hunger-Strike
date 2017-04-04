#include <Parallax.h>
#include <TextureLoader.h>

#pragma comment(lib, "opengl32.lib")

TextureLoader *Btex = new TextureLoader();

Parallax::Parallax()
{
    Xmax =  1.0f;
    Xmin =  0.0f;
    Ymax =  0.0f;
    Ymin =  1.0f;
}

Parallax::~Parallax()
{
    //dtor
}

void Parallax::PrlxInit(char *FileName){

    Btex->Binder();
    Btex->BindTexture(FileName);
}

void Parallax::scroll(bool Auto, string Dir, float speed)
//direction: x, -x, y, -y
{
    if(Auto)
    {
        if(Dir == "x")
        {  // cout<< Dir <<endl;
            Xmin += speed;
            Xmax += speed;
        }
        else if(Dir == "-x")
        {
            Xmin -= speed;
            Xmax -= speed;
        }
        else if(Dir == "y")
        {
            Ymin -= speed;
            Ymax -= speed;
        }
        else
        {
            Ymin  += speed;
            Ymax  += speed;
        }
    }
}

void Parallax::DrawSquare(float width, float height){
  glColor3f(1.0,1.0,1.0);
  Btex->Binder();
  glBegin(GL_POLYGON);
    glTexCoord2f(Xmin, Ymin);
    glVertex3f(-1*width/height, -1,  -8.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(Xmax, Ymin);
    glVertex3f( 1*width/height, -1,  -8.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(Xmax, Ymax);
    glVertex3f( 1*width/height,  1,  -8.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(Xmin, Ymax);
    glVertex3f(-1*width/height,  1,  -8.0f);  // Top Left Of The Texture and Quad
   glEnd();

    }
