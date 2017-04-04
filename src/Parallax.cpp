#include "Parallax.h"
#include "TextureLoader.h"

#pragma comment(lib, "opengl32.lib")

TextureLoader *Btex = new TextureLoader();

Parallax::Parallax()
{
	mX = 0.0f;
	mY = 0.0f;
}

Parallax::~Parallax()
{
	//dtor
}

void Parallax::PrlxInit( char *FileName )
{

	Btex->Binder();
	Btex->BindTexture( FileName );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}

void Parallax::scroll( bool Auto, string Dir, float speed )
//direction: x, -x, y, -y
{
	/*if( Auto )
	{
		if( Dir == "x" )
		{  // cout<< Dir <<endl;
			Xmin += speed;
			Xmax += speed;
		}
		else if( Dir == "-x" )
		{
			Xmin -= speed;
			Xmax -= speed;
		}
		else if( Dir == "y" )
		{
			Ymin -= speed;
			Ymax -= speed;
		}
		else
		{
			Ymin += speed;
			Ymax += speed;
		}
	}*/
}

void Parallax::scrollTo( float x, float y )
{
	mX = x;
	mY = y;
}

void Parallax::DrawSquare( float width, float height )
{
	float Xmin = mX;
	float Xmax = mX + 1.0f;
	float Ymin = mY + 1.0f;
	float Ymax = mY;
	glColor3f( 1.0, 1.0, 1.0 );
	Btex->Binder();
	glBegin( GL_POLYGON );
	glTexCoord2f( Xmin, Ymin );
	glVertex3f( -1 * width / height, -1, -4.f );  // Bottom Left Of The Texture and Quad
	glTexCoord2f( Xmax, Ymin );
	glVertex3f( 1 * width / height, -1, -4.f );  // Bottom Right Of The Texture and Quad
	glTexCoord2f( Xmax, Ymax );
	glVertex3f( 1 * width / height, 1, -4.f );  // Top Right Of The Texture and Quad
	glTexCoord2f( Xmin, Ymax );
	glVertex3f( -1 * width / height, 1, -4.f );  // Top Left Of The Texture and Quad
	glEnd();

}
