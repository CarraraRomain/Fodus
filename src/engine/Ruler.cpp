#include "Ruler.hpp"



void Ruler::execute(Command* com, Etat* state)
{
	switch (com->type)
	{
	case Move:
		LOG(DEBUG) << "Executing Move Command";
		{
			MoveCommand* move_com = dynamic_cast<MoveCommand*>(com);
			// TODO Optimization
			int x = move_com->posX + state->getAttribute("posX", move_com->Uid);
			int y = move_com->posY + state->getAttribute("posY", move_com->Uid);
			bool rc = checkMove(state, x, y, move_com->Uid);
			LOG(DEBUG) << "X:" << x << ", Y:" << y;
			if (rc)
			{
				MoveAction* action = new MoveAction(move_com->Uid, x, y);
				m_action_list->push_back(action);

			}else LOG(DEBUG) << move_com->Uid << " can't move here";
		}
		break;
	case Attack:
//		if (checkAttack(state, std::stoi(com->getPayload("UID1")),
//			std::stoi(com->getPayload("UID"))))
			//create ActionAttack;
//			LOG(DEBUG) << "Attacking UID1 " + com->getPayload("UID1");
		break;
	}
	update();
}

void Ruler::update()
{
	for (int i = 0; i < m_action_list->size();i++)
	{
		(*m_action_list)[i]->execute(m_state);
		m_action_list->remove(i);
	}
}

bool Ruler::checkMove(Etat* state, int x, int y, int uid)
{

	// find elt in x, y to check its depth ; if d > 0 return false;
	ElementList* liste = state->getList();
	for (int i = 0; i < state->getSize(); i++)
	{
		if ((*liste)[i]->getX() == x && (*liste)[i]->getY() == y && (*liste)[i]->getD() > 0)
		{
			LOG(DEBUG) << (*liste)[i]->getKey() << " is here";
			return false;
		}
	}
	//if ((x + y) >state->getAttribute("deplacement", uid)) return false;
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