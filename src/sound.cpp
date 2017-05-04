#include "sound.h"

ISoundEngine* engine = createIrrKlangDevice();

sound::sound()
{
    //ctor
}

sound::~sound()
{
    engine->drop();
    //dtor
}
int sound::soundinit()
{
    if(!engine)
    {
        //cout<<"Error...";
        return 0;
    }
    return 1;

}

void sound::playMusic(char* File)
{
    engine->play2D(File,true);
}

void sound::playSound(char* File)
{
    engine->play2D(File,false,false);

}
