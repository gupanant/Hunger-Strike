#include "Inputs.h"
int startflag=1;

Inputs::Inputs()
{
	Mouse_Translate = false;
	Mouse_Roatate = false;
}

Inputs::~Inputs()
{
	//dtor
}

void Inputs::KeyEnv( Parallax *Bk1, float speed )
{
	switch( wParam )
	{
	case VK_LEFT:


	// Process the LEFT ARROW key.
	break;

	case VK_RIGHT:
	// Process the RIGHT ARROW key.
	break;

	case VK_UP:
	//    Bk1->Ymin += speed;
	//    Bk1->Ymax += speed;
	   // Process the UP ARROW key.
	break;

	case VK_DOWN:
	//   Bk1->Ymin -= speed;
	//   Bk1->Ymax -= speed;
	  // Process the DOWN ARROW key.
	break;
	}
}

void Inputs::KeyPressed( Player *player )
{
	switch( wParam )
	{
	case VK_LEFT:
	player->StartMove( Player::Left );
	break;

	case VK_RIGHT:
	player->StartMove( Player::Right );
	break;

	case VK_UP:
	player->Jump();
	break;

	case VK_DOWN:
	player->Slide();
	break;

	case VK_RETURN:
    startflag=0;
    break;

	}
}


void Inputs::KeyUp( Player *player )
{
	if( wParam == VK_LEFT || wParam == VK_RIGHT )
		player->Stop();

	if( wParam == VK_DOWN )
		player->StopSliding();
}

void Inputs::MouseEventDown( Model *Model, double x, double y )
{
	prev_Mouse_X = x;
	prev_Mouse_Y = y;

	switch( wParam )
	{
	case MK_LBUTTON:
	Mouse_Roatate = true;
	break;

	case MK_RBUTTON:
	Mouse_Translate = true;
	break;
	case MK_MBUTTON:

	break;

	default:
	break;
	}
}

void Inputs::MouseEventUp()
{
	Mouse_Translate = false;
	Mouse_Roatate = false;
}

void Inputs::MouseWheel( Model *Model, double Delta )
{
	Model->Zoom += Delta / 100;
}

void Inputs::MouseMove( Model *Model, double x, double y )
{
	if( Mouse_Translate )
	{
		Model->TranslateX += ( x - prev_Mouse_X ) / 100;
		Model->TranslateY += ( y - prev_Mouse_Y ) / 100;

		prev_Mouse_X = x;
		prev_Mouse_Y = y;
	}

	if( Mouse_Roatate )
	{
		Model->RotateY += ( x - prev_Mouse_X ) / 3;
		Model->RotateX += ( y - prev_Mouse_Y ) / 3;

		prev_Mouse_X = x;
		prev_Mouse_Y = y;
	}
}

