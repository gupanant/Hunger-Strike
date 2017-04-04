#include <Model.h>
#include <TextureLoader.h>

#pragma comment(lib, "opengl32.lib")

TextureLoader *tex = new TextureLoader();

Model::Model()
{
   RotateX  = 0.0;
   RotateY  = 0.0;
   RotateZ  = 0.0;
   Zoom     = -8.0;
   TranslateX = 0.0;
   TranslateY = 0.0;
}

Model::~Model()
{
    //dtor
}

void Model::ModelInit(char *fileName)
{
    tex->Binder();
    tex->BindTexture(fileName);
}

void Model::DrawModel()
{
    tex->Binder();
    glTranslated(TranslateX,-TranslateY,Zoom);
    glRotated(RotateX,1,0,0);
    glRotated(RotateY,0,1,0);
    glRotated(RotateZ,0,0,1);
    glutSolidTeapot(1.5);
}
