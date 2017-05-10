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

	float width = mTex->width * mR;
	float height = mTex->height * mR;

	// Center and scale according to radius.
	glTranslatef( mX - width * 0.5f, mY - height * 0.5f, -2.0f );

	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, -1.5f );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( width, 0.0f, -1.5f );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( width, height, -1.5f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( 0.0f, height, -1.5f );
	glEnd();

	glPopMatrix();

}

void Collider::Update( float dt )
{
	mX -= mSpeed * dt;
}

