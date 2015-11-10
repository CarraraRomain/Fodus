#include "MoveAction.hpp"

void MoveAction::execute(Etat e)
{
	e.setAttribute("posX", posX, uid);
	e.setAttribute("posY", posY, uid);
}

MoveAction::MoveAction(int newUid, int newPosX, int newPosY)
{
	uid = newUid;
	posX = newPosX;
	posY = newPosY;
}

MoveAction::~MoveAction()
{
}
