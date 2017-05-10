#ifndef collider_H
#define collider_H

#include <string>
#include "TextureLoader.h"

class Collider
{
public:

	Collider( float x, float y, float radius, float speed, TextureLoader* texture );

	void Update(float dt);
	void Render();
	bool Collides( float otherx, float othery, float otherradius );

	TextureLoader* mTex;

	float mX;
	float mY;
	float mR;
	float mSpeed;

private:


};

#endif