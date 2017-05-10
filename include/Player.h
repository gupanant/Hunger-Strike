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
		Falling,
		Sliding,
		Dying
	};

	enum Direction
	{
		None,
		Left,
		Right
	};

	Player( float height = 1 );
	virtual ~Player();

	void Init();

	void StartMove( Direction d );
	void Jump();
	void Stop();
	void Slide();
	void StopSliding();
	void Die();

	void Render();
	void Update( float dt, float screenheight );


	float mX;
	float mY;
	float mSize;

	float mGroundHeight;
	float mJumpHeight;

	TextureLoader* mCurrentTex;

	bool IsDead() { return mDead; }
	bool IsDying() { return mState == Dying; }


	void Reset();

protected:

private:
	void drawPlayer();


	int mRunFrame;
	int mJumpFrame;
	int mFallFrame;
	int mDieFrame;

	bool mDead;

	int mState;
	int mDirection;
};

#endif // PLAYER_H
