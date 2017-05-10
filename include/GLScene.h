#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h> // Header File For Windows
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <time.h>

#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>

#include "collider.h"
#include "particle.h"

#define HIGHSCOREFILE "highscores"

enum States
{
	STATE_INGAME,
	STATE_TITLE,
	STATE_MENU,
	STATE_HELP,
	STATE_GAMEOVER,
	STATE_EXIT,
	STATE_ASKNAME,
	STATE_HIGHSCORE
};
using namespace std;
class GLScene
{

public:
	GLScene();
	virtual ~GLScene();
	GLvoid ReSizeGLScene( GLsizei width, GLsizei height );
	GLint InitGL();
	GLint DrawGLScene();

	int  WindowMsg( HWND,		// Handle For This Window
		UINT,		// Message For This Window
		WPARAM,		// Additional Message Information
		LPARAM );

	int mState;
	std::string mName;

	bool mRunning;

	double RotateX;
	double RotateY;
	double RotateZ;
	double Zoom;
	double TranslateX;
	double TranslateY;

	float ScreenHeight;
	float ScreenWidth;

	std::vector< Collider > mColliders;
	std::vector< Collider > mBullets;

	struct Score
	{
		std::string name;
		int score;
	};
	std::vector< Score > mHighScores;

protected:

	void SaveHighScores( std::string filename );
	void LoadHighScores( std::string filename );
	void AddHighScore( Score s );

private:

	int mScore;
	int mLifes;
	int mTime;

	float mLastx;

	ParticleSystem mPS;

	void ResetGameState();

	void Shoot();

	void DrawIngame();
	void DrawTitleScreen();
	void DrawMenuScreen();
	void DrawHelpScreen();
	void DrawGameOverScreen();
	void DrawExitScreen();
	void DrawAskNameScreen();
	void DrawHighScoreScreen();

	void OnKeyUp( WPARAM vkkey );

};

#endif // GLSCENE_H
