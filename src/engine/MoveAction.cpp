#include "MoveAction.hpp"
#include "../global.hpp"

void MoveAction::execute(Etat& e)
{
	e.setAttribute("posX", posX, uid);
	e.setAttribute("posY", posY, uid);
	switch(dir)
	{
	case MoveForward:
		e.setAttribute("direction", "Forward", uid);
		break;
	case MoveBackward:
		e.setAttribute("direction", "Backward", uid);
		break;
	case MoveLeft:
		e.setAttribute("direction", "Left", uid);
		break;
	case MoveRight:
		e.setAttribute("direction", "Right", uid);
		break;

	}
	//LOG(DEBUG) << uid << " is now at X:" << posX << ", Y:" << posY << ", Dir" << dir ;
}

MoveAction::MoveAction(int newUid, int newPosX, int newPosY, AnimationType type)
	: Action(Move)
{
	uid = newUid;
	posX = newPosX;
	posY = newPosY;
	dir = type;
}

MoveAction::~MoveAction()
{
}
