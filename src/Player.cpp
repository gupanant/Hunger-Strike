#include "Player.h"

Timer *T = new Timer();
float t =0;

TextureLoader runTtex[23];
TextureLoader stndTtex[2];
TextureLoader jumpTtex[8];


Player::Player()
{
    //ctor
    runSpeed =0;
    jumpSpeed =0;
    actionTrigger=0;

}

Player::~Player()
{
    //dtor
}

void Player::playerInit()
{
    T->Start();

    Player_x = -0.8;
    Player_y = -0.9;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stndTtex[0].BindTexture("images/player/play.png");

    jumpTtex[0].BindTexture("images/player/playerjump0.png");
    jumpTtex[1].BindTexture("images/player/playerjump1.png");
    jumpTtex[2].BindTexture("images/player/playerjump2.png");
    jumpTtex[3].BindTexture("images/player/playerjump3.png");
    jumpTtex[4].BindTexture("images/player/playerjump4.png");
    jumpTtex[5].BindTexture("images/player/playerjump5.png");
    jumpTtex[6].BindTexture("images/player/playerjump6.png");
    jumpTtex[7].BindTexture("images/player/playerjump7.png");

    runTtex[0].BindTexture("images/player/player0.png");
    runTtex[1].BindTexture("images/player/player1.png");
    runTtex[2].BindTexture("images/player/player2.png");
    runTtex[3].BindTexture("images/player/player3.png");
    runTtex[4].BindTexture("images/player/player4.png");
    runTtex[5].BindTexture("images/player/player5.png");
    runTtex[6].BindTexture("images/player/player6.png");
    runTtex[7].BindTexture("images/player/player7.png");
    runTtex[8].BindTexture("images/player/player8.png");
    runTtex[9].BindTexture("images/player/player9.png");
    runTtex[10].BindTexture("images/player/player10.png");
    runTtex[11].BindTexture("images/player/player11.png");
    runTtex[12].BindTexture("images/player/player12.png");
    runTtex[13].BindTexture("images/player/player13.png");
    runTtex[14].BindTexture("images/player/player14.png");
    runTtex[15].BindTexture("images/player/player15.png");
    runTtex[16].BindTexture("images/player/player16.png");
    runTtex[17].BindTexture("images/player/player17.png");
    runTtex[18].BindTexture("images/player/player18.png");
    runTtex[19].BindTexture("images/player/player19.png");
    runTtex[20].BindTexture("images/player/player20.png");
    runTtex[21].BindTexture("images/player/player21.png");
    runTtex[22].BindTexture("images/player/player22.png");
}

void Player::Action(int action)
{
     switch(action)
    {

   case 0:

        glPushMatrix();
        glTranslated(-0.8,-0.75,-2.0);
        stndTtex[0].Binder();
        drawPlayer();
        glPopMatrix();
        break;

    case 1:

        glPushMatrix();

        Player_x = -0.8;
        Player_y = -0.9;

        glTranslated(Player_x,Player_y,-2.0);

       if(T->GetTicks()>15)
        {
            runSpeed++;
            T->Reset();
        }
        runSpeed = runSpeed%23;

        runTtex[runSpeed].Binder();
        drawPlayer();
        glPopMatrix();

        break;


     case 2:

        glPushMatrix();

        glTranslated(Player_x,Player_y,-2.0);

        if(T->GetTicks()>15)
        {
            jumpSpeed ++;
            T->Reset();
        }

        jumpSpeed  = jumpSpeed %7;
        jumpTtex[jumpSpeed].Binder();

        drawPlayer();
        glPopMatrix();
        break;
    }
}

void Player::drawPlayer()
{
        glScaled(Player_size[0],Player_size[1],Player_size[2]);

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
