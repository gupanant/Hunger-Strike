#ifndef PARTICLE_H
#define PARTICLE_H
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <stdlib.h>
#define MAX_DROPS 50000
#define PI 3.141592653589
#define GRAVITY -0.005

class particle
{
    public:
        particle();
        virtual ~particle();

        typedef struct {
            bool alive;
            float xpos;
            float ypos;
            //float zpos;
            float xdir, ydir, mass;
            int NumDrops;
        } Particle;
        int NumDrops;
        void generateP();
        void lifeTime();
        void drawParticles();
        Particle drops[MAX_DROPS];

    protected:

    private:
};

#endif // PARTICLE_H
