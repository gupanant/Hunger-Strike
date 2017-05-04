#ifndef SOUND_H
#define SOUND_H

#include <SNDS/irrKlang.h>
#include <stdlib.h>
#include <iostream>

#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

class sound
{
    public:
        sound();
        virtual ~sound();

        int soundinit();
        void playMusic(char *);
        void playSound(char *);

    protected:

    private:
};

#endif // SOUND_H
