#include "Ruler.hpp"

void Ruler::execute(Command* com, Etat* state)
{
	switch (com->type)
	{
	case Move:
		if (checkMove(state, com->getPayload()["X"].GetInt() , com->getPayload()["Y"].GetInt(), com->getPayload()["Uid"].GetInt()));
		//create action here
		//ActionFactory.create("Move",CommandeUID,CommandeX,CommandeY);
		break;
	case Attack:
		if (checkAttack(state, com->getPayload()["Uid1"].GetInt(), com->getPayload()["Uid2"].GetInt()));
		//create ActionAttack;
		break;
	}
}

bool Ruler::checkMove(Etat* state, int posX, int posY, int uid)
{
	int i = 0;
	ElementList* liste = state->getList();
	for (i = 0; i < state->getSize(); i++)
	{
		if ((*liste)[i]->getX() == posX && (*liste)[i]->getY() == posY && (*liste)[i]->getUid() != 0)
			return false;
	}
	int x = posX - (*liste)[(*liste).findUid(uid)]->getX();
	int y = posY - (*liste)[(*liste).findUid(uid)]->getY();
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (x + y >(*liste)[(*liste).findUid(uid)]->getAttribute("deplacement")) return false;
	return true;
}

bool Ruler::checkAttack(Etat* state, int uid1, int uid2)
{
	ElementList* liste = state->getList();
	
	int x = (*liste)[(*liste).findUid(uid1)]->getAttribute("posX") - (*liste)[liste->findUid(uid2)]->getAttribute("posX");
	int y = (*liste)[(*liste).findUid(uid1)]->getAttribute("posY") - (*liste)[liste->findUid(uid2)]->getAttribute("posY");

	if (x < 0) x = -x;
	if (y < 0) y = -y;

	if (x + y>(*liste)[(*liste).findUid(uid1)]->getAttribute("Move"))return false;
	else return true;
}