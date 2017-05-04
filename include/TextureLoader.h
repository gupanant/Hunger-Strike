#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <Windows.h>
#include <SOIL.h>
#include <gl/gl.h>			// Header File For The OpenGL32 Library


class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();
        void BindTexture(const char *);
        void Bind();
        unsigned char* image;
        int width, height;
        GLuint tex;
    protected:

    private:
};

#endif // TEXTURELOADER_H
