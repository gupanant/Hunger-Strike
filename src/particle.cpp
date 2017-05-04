#include "particle.h"

particle::particle()
{
    //ctor
}

particle::~particle()
{
    //dtor
}
double drand48(){
    return (rand()%1000)/1000.0;
}

void particle::generateP()
{
    int i, newdrops=drand48()*60;

    if(NumDrops + newdrops > MAX_DROPS)
        newdrops = MAX_DROPS - NumDrops;

    for(i=NumDrops;i<NumDrops + newdrops;i++){
        drops[i].alive= true;
        drops[i].xpos = -0.8 + 0.1 * drand48();
        drops[i].ypos = 0.8 + 0.1 * drand48();
        //drops[i].zpos = -0.5;
        drops[i].xdir = 0.0075 + 0.025 * drand48();
        drops[i].ydir = 0.0;
        drops[i].mass = 0.5 + 0.5 * drand48();
    }
    NumDrops +=newdrops;
    if(NumDrops >= MAX_DROPS) NumDrops = 0;

}

void particle::lifeTime()
{
    int i;
    for(i=0;i<NumDrops;i++)
    {
        if(drops[i].alive)
        {
            if(drops[i].ypos + GRAVITY*drops[i].mass < 0.0){ drops[i].ydir = -drops[i].ydir;}
            else {drops[i].ydir += GRAVITY * drops[i].mass;}
            drops[i].xpos += drops[i].xdir;
            drops[i].ypos += drops[i].ydir;

            if(drops[i].ypos < -5.0 && drops[i].xpos > 5.0)
                drops[i].alive = false;
        }
    }
}

void particle::drawParticles()
{
    glColor3f(0.0,0.0,1.0);
    glPointSize(3);
    glBegin(GL_POINTS);

    for(int i=0; i < NumDrops; i++)
    {
        if(drops[i].alive)
        {
            glVertex3f(drops[i].xpos, drops[i].ypos, -5.0);
        }
    }

    glEnd();
}
