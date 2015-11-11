#include "MoveAction.hpp"
#include "../global.hpp"

void MoveAction::execute(Etat& e)
{
	e.setAttribute("posX", posX, uid);
	e.setAttribute("posY", posY, uid);
	LOG(DEBUG) << uid << " is now at X:" << posX << ", Y:" << posY;
}

MoveAction::MoveAction(int newUid, int newPosX, int newPosY)
	: Action(Move)
{
	uid = newUid;
	posX = newPosX;
	posY = newPosY;
}

MoveAction::~MoveAction()
{
}
