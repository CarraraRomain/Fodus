#include "Ruler.hpp"

void Ruler::execute(Command* com, Etat* state)
{
	switch (com->type)
	{
	case Move:
		if (checkMove(state, std::stoi(com->getPayload("X")),
			std::stoi(com->getPayload("Y")), std::stoi(com->getPayload("UID"))))
			LOG(DEBUG) << "Moving UID " + com->getPayload("UID");
			//create action here
			//ActionFactory.create("Move",CommandeUID,CommandeX,CommandeY);
		break;
	case Attack:
		if (checkAttack(state, std::stoi(com->getPayload("UID1")),
			std::stoi(com->getPayload("UID"))))
			//create ActionAttack;
			LOG(DEBUG) << "Attacking UID1 " + com->getPayload("UID1");
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
	int x = posX - state->getAttribute("posX",uid);
	int y = posY - state->getAttribute("posY", uid);
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (x + y >state->getAttribute("deplacement", uid)) return false;
	return true;
}

bool Ruler::checkAttack(Etat* state, int uid1, int uid2)
{
	ElementList* liste = state->getList();
	
	int x = state->getAttribute("posX", uid1) - state->getAttribute("posX", uid2);
	int y = state->getAttribute("posY", uid1) - state->getAttribute("posX", uid2);

	if (x < 0) x = -x;
	if (y < 0) y = -y;

	if (x + y > state->getAttribute("portee", uid1))return false;
	else return true;
}