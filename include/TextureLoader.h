#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <SOIL.h>
#include <gl/gl.h>			// Header File For The OpenGL32 Library


class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();
        void BindTexture(char *);
        void Binder();
        unsigned char* image;
        int width, height;
        GLuint tex;
    protected:

    private:
};

#endif // TEXTURELOADER_H
