#include "particle.h"

ParticleSystem::ParticleSystem()
{
	//ctor
}

ParticleSystem::~ParticleSystem()
{
	//dtor
}
float RandomFloat()
{
	return (float)rand() / (float)RAND_MAX;
}

void ParticleSystem::GenerateRain( float offset, float width, float height )
{
	if( mParticles.size() > 4000 )
		return;

	Particle p;
	p.xpos = offset + RandomFloat() * width;
	p.ypos = height * 0.5f + RandomFloat() * height;
	p.xdir = 0.0075f * width + 0.025f * RandomFloat() * width;
	p.ydir = -0.4f * height;
	p.mass = 0.5f + 0.5f * RandomFloat();
	p.life = 100.0f;
	p.r = 0.2f + RandomFloat() * 0.2f;
	p.g = 0.2f + RandomFloat() * 0.2f;
	p.b = 0.6f + RandomFloat() * 0.4f;

	mParticles.push_back( p );
}

void ParticleSystem::GenerateExplosion( float x, float y, int n )
{
	for( int i = 0; i < n; ++i )
	{
		Particle p;
		p.xpos = x;
		p.ypos = y;

		// Generate a random direction and normalize it.
		p.xdir = RandomFloat() - 0.5f;
		p.ydir = RandomFloat() - 0.5f;
		float len = sqrt( p.xdir * p.xdir + p.ydir * p.ydir );
		p.xdir /= len;
		p.ydir /= len;

		// Generate a random velocity.
		float velocity = RandomFloat() * 650.0f + 200.0f;
		p.xdir *= velocity;
		p.ydir *= velocity;

		p.r = 0.5f + RandomFloat() * 0.5f;
		p.g = RandomFloat() * 0.8f;
		p.b = RandomFloat() * 0.5f;

		p.mass = 50.0f + 50.0f * RandomFloat();
		p.life = 0.5f + RandomFloat() * 0.5f;
		mParticles.push_back( p );
	}
}

void ParticleSystem::Update( float dt, float miny )
{
	std::vector<Particle >::iterator i;
	for( i = mParticles.begin(); i != mParticles.end(); )
	{
		i->life -= dt;
		i->ydir += (GRAVITY * i->mass) * dt;

		i->xpos += i->xdir * dt;
		i->ypos += i->ydir * dt;

		if( i->life < 0.0f || i->ypos < miny )
			i = mParticles.erase( i );
		else i++;
	}
}

void ParticleSystem::drawParticles()
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	//glLoadIdentity(); 

	glDisable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );
	
	glLineWidth( 3.0f );

	glBegin( GL_LINES );

	for( size_t i = 0; i < mParticles.size(); i++ )
	{
		Particle drop = mParticles[i];
		float x = drop.xpos;
		float y = drop.ypos;
		float xv = drop.xdir;
		float yv = drop.ydir;
		glColor4f( drop.r, drop.g, drop.b, 1.0f );

		glVertex3f( x, y, 0.0f );
		glVertex3f( x + xv * 0.1f, y + yv * 0.1f, 0.0f );
	}
	glEnd();
	glPopMatrix();

	glEnable( GL_LIGHTING );
	glEnable( GL_TEXTURE_2D );
}
