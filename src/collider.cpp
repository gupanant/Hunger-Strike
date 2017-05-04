#include "collider.h"

Collider::Collider( float x, float y, float radius, float speed, TextureLoader* texture )
{
	mX = x;
	mY = y;
	mR = radius;
	mTex = texture;
	mSpeed = speed;
}

void Collider::Render()
{
	glPushMatrix();
	mTex->Bind();

	// Center and scale according to radius.
	glTranslatef( mX - mR * 0.5f, mY - mR * 0.5f, -2.0f );
	glScaled( mR, mR, 1.0f );

	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, -1.5f );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( 1.0f, 0.0f, -1.5f );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( 1.0f, 1.0f, -1.5f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( 0.0f, 1.0f, -1.5f );
	glEnd();

	glPopMatrix();

}

bool Collider::Collides( float x, float y, float r )
{
	float dx = mX - x;
	float dy = mY - y;
	/* pikachu testing the collision */
	float distance2 = dx * dx + dy * dy;
	float radius2 = mR * mR + r * r;
    //cout<<"distance"<<distance2<<"tessssss"<<radius2;
	return distance2 < radius2;

}

void Collider::Update( float dt )
{
	mX -= mSpeed * dt;
}

