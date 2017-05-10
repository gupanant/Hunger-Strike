#ifndef PARTICLE_H
#define PARTICLE_H

#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <stdlib.h>
#include <vector>

#define MAX_DROPS 50000
#define PI 3.141592653589
#define GRAVITY -9.8

class ParticleSystem
{
    public:
        ParticleSystem();
        virtual ~ParticleSystem();

        struct Particle
		{
            float xpos;
            float ypos;
			float xdir;
			float ydir;
			float mass;
			float life;
			float r;
			float g;
			float b;
        };
        void GenerateRain( float offset, float width, float height );
		void GenerateExplosion( float x, float z, int nparticles );
        void Update( float dt, float miny );
        void drawParticles();

		std::vector< Particle > mParticles;

    protected:

    private:
};

#endif // PARTICLE_H
