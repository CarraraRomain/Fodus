#include "Ruler.hpp"


Ruler::Ruler(Etat& state): m_state(state)
{
	m_action_list.reset(new ActionList);
}

Ruler::~Ruler()
{
}
/**
 * Execute a command and generate an action against a state
 */
void Ruler::execute(Command* com, Etat* state)
{
	LOG(DEBUG) << "before map";
	createMap(state);
	LOG(DEBUG) << "after map";
	switch (com->type)
	{
	case Move:
		LOG(DEBUG) << "Ruler : exec Move Command";
		{
			MoveCommand* move_com = dynamic_cast<MoveCommand*>(com);
			// TODO Optimization
			int x = move_com->posX + state->getAttribute("posX", move_com->Uid);
			int y = move_com->posY + state->getAttribute("posY", move_com->Uid);
			if (checkMove(state, x, y, move_com->Uid))
			{
				MoveAction* action = new MoveAction(move_com->Uid, x, y, move_com->dir);
				m_action_list->push_back(action);

			}
			else LOG(DEBUG) << move_com->Uid << " can't move at " << "X:" << x << ", Y:" << y;
		}
		break;
	case Attack:
		// TODO Implementation
//		if (checkAttack(state, std::stoi(com->getPayload("UID1")),
//			std::stoi(com->getPayload("UID"))))
			//create ActionAttack;
//			LOG(DEBUG) << "Attacking UID1 " + com->getPayload("UID1");
		break;
	}
	update();
}
/**
 * Apply action on a state
 */
void Ruler::update()
{
	for (int i = 0; i < m_action_list->size();i++)
	{
		(*m_action_list)[i]->execute(m_state);
		m_action_list->remove(i);
	}
}

/**
 * Check movement legitimacy
 */
bool Ruler::checkMove(Etat* state, int x, int y, int uid)
{
	LOG(DEBUG) << "propagate with" << state->getAttribute("posX", uid) << state->getAttribute("posY", uid), state->getAttribute("deplacement", uid);
	propagate(state->getAttribute("posX", uid), state->getAttribute("posY", uid), state->getAttribute("deplacement", uid));
	LOG(DEBUG) << "propagate done";
	if(mapCharacter[x][y] > 0) return true;
	else return false;

	/*ElementList* liste = state->getList();
	for (int i = 0; i < state->getSize(); i++)
	{
		// if elt is in X, Y, with depth > 0 and not void ("VOID_1" elt)
		if ((*liste)[i]->getX() == x &&
			(*liste)[i]->getY() == y && 
			(*liste)[i]->getD() > 0  &&
			(*liste)[i]->getKey() != "VOID_1")
		{
			LOG(DEBUG) << (*liste)[i]->getKey() << " is here";
			return false;
		}
	}
	// if Elt would be out of window boundaries
	return !(x < 0 || x >= WIDTH) && !(y < 0 || y >= HEIGHT);
	//if ((x + y) >state->getAttribute("deplacement", uid)) return false;*/
}

/**
 * Not used yet
 */
bool Ruler::checkAttack(Etat* state, int uid1, int uid2)
{
	ElementList* liste = state->getList();
	
	int x = state->getAttribute("posX", uid1) - state->getAttribute("posX", uid2);
	int y = state->getAttribute("posY", uid1) - state->getAttribute("posX", uid2);

	if (x < 0) x = -x;
	if (y < 0) y = -y;

	return x + y <= state->getAttribute("portee", uid1);
}

void Ruler::createMap(Etat * state)
{
	int i, j;

	map.resize(WIDTH);
	for (int i = 0; i < WIDTH; ++i)
		map[i].resize(HEIGHT);

	for (i = 0; i < WIDTH; i++)
		for (j = 0; j < HEIGHT; j++) {
			map[i][j] = 0;
		}

	mapCharacter.resize(WIDTH);
	for (int i = 0; i < WIDTH; ++i)
		mapCharacter[i].resize(HEIGHT);

	for (i = 0; i < WIDTH; i++)
		for (j = 0; j < HEIGHT; j++) {
			mapCharacter[i][j] = 0;
		}

	ElementList* liste = state->getList();
	for (int i = 0; i < state->getSize(); i++)
	{
		if((*liste)[i]->getKey() != "VOID_1") map[(*liste)[i]->getX()][(*liste)[i]->getY()] = (*liste)[i]->getD();
	}
}

void Ruler::propagate(int posX, int posY, int value)
{
	mapCharacter[posX][posY] = value;
	if (value > 1) {
		if(posX > 0)
			if (map[posX - 1][posY] < 1 && mapCharacter[posX - 1][posY] < value) propagate(posX - 1, posY, value - 1);
		if(posY > 0)
			if (map[posX][posY - 1] < 1 && mapCharacter[posX][posY - 1] < value) propagate(posX, posY - 1, value - 1);
		if (posY < HEIGHT - 1)
			if (map[posX][posY + 1] < 1 && mapCharacter[posX][posY + 1] < value) propagate(posX, posY + 1, value - 1);
		if (posX < WIDTH - 1)
			if (map[posX + 1][posY] < 1 && mapCharacter[posX + 1][posY] < value) propagate(posX + 1, posY, value - 1);
	}
}


