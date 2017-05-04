#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include "Model.h"
#include "Parallax.h"
#include "Player.h"

using namespace std;
class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void KeyPressed(Player *);
        void KeyEnv(Parallax *,float);
        void KeyUp(Player *);
        void MouseEventDown(Model *,double ,double);
        void MouseEventUp();
        void MouseWheel(Model *,double);
        void MouseMove(Model *,double ,double );
        int startFlag;
        double prev_Mouse_X;
        double prev_Mouse_Y;
        bool Mouse_Translate;
        bool Mouse_Roatate;

        WPARAM wParam;
    protected:

    private:
};

#endif // INPUTS_H
