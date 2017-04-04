#ifndef PLAYER_H
#define PLAYER_H

#include <sstream>

#include "TextureLoader.h"


class Player
{
public:
	enum States
	{
		Standing,
		Running,
		Jumping,
		Falling
	};

	enum Direction
	{
		None,
		Left,
		Right
	};

	Player();
	virtual ~Player();

	void playerInit();

	void StartMove( Direction d );
	void Jump();
	void Stop();

	void Render();
	void Update();


	float mX;
	float mY;


protected:

private:
	void drawPlayer();


	float Player_size[3] = { 1.0,1.0,1.0 };
	float Vertices[4][3] = { { 0.0, 0.0, -1.5 },{ 1.0, 0.0, -1.5 },{ 1.0, 1.0, -1.5 },{ 0.0, 1.0, -1.5 } };

	int mRunFrame;
	int mJumpFrame;
	int mFallFrame;

	int mState;
	int mDirection;
};

#endif // PLAYER_H
