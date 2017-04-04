#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
    //ctor
}

TextureLoader::~TextureLoader()
{
    //dtor
}
void TextureLoader::Binder()
{
    glBindTexture(GL_TEXTURE_2D, tex);
}

void TextureLoader::BindTexture(char *FileName)
{
    glGenTextures(1, &tex);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, tex);
    image = SOIL_load_image(FileName, &width, &height, 0, SOIL_LOAD_RGBA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);

    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // Repeat the pattern
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}
