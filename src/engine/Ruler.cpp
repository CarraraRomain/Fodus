#include "Ruler.hpp"

#include "Engine.hpp"
#include "../state/ElementList.hpp"


Ruler::Ruler(Engine* e, Etat& state): m_state(state), m_engine(e)
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
	bool success = false;
	switch (com->type)
	{
	case Move:
		LOG(DEBUG) << "Ruler : exec Move Command";
		{
			MoveCommand* move_com = dynamic_cast<MoveCommand*>(com);
			// TODO Optimization
			int x, y;

			if(move_com->posX > 50)x = move_com->posX - 100 + state->getAttribute("posX", move_com->Uid);
			else x = move_com->posX;
			if(move_com->posY > 50)y = move_com->posY - 100 + state->getAttribute("posY", move_com->Uid);
			else y = move_com->posY;

			if (checkMove(state, x, y, move_com->Uid, move_com->player))
			{
				//MoveAction* action = new MoveAction(move_com->Uid, x, y, move_com->dir);
				//m_action_list->push_back(action);
				createMove(state, x, y, move_com->Uid, move_com->player);
				m_engine->getPlayer(move_com->player).move(move_com->Uid);
				success = true;
			}
			else LOG(DEBUG) << move_com->Uid << " can't move at " << "X:" << x << ", Y:" << y;
		}
		break;

	case Attack:

		LOG(DEBUG) << "Ruler : exec Attack Command";
		{
			AttackCommand* attack_com = dynamic_cast<AttackCommand*>(com);

			if (checkAttack(state, attack_com->uid1, attack_com->uid2, attack_com->player))
			{
				createAttack(state, attack_com->uid1, attack_com->uid2);
				m_engine->getPlayer(attack_com->player).attack(attack_com->uid1);
				success = true;
			}
			else LOG(DEBUG) << attack_com->uid1 << " can't attack " << attack_com->uid2;
		}
		break;
	}
	if(success) update();
	else throw std::logic_error("Bad Command");
}
/**
 * Apply action on a state
 */
void Ruler::update()
{
	for (int i = m_action_list->size()-1; i >= 0;i--)
	{
		(*m_action_list)[i]->execute(m_state);
		m_action_list->remove(i);
	}
}

/**
 * Check movement legitimacy
 */
bool Ruler::checkMove(Etat* state, int x, int y, int uid, int player)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT || m_engine->getPlayer(player).hasMoved(uid)) return false;
	
	if(mapCharacter[uid][x][y] > 0) return true;
	else return false;
}

bool Ruler::createMove(Etat * state, int x, int y, int uid, int player)
{
	int i;
	for (i = 0; i < HEIGHT + WIDTH; i++)
	{
		if (x > 0)
		{
			if (mapCharacter[uid][x - 1][y] > mapCharacter[uid][x][y])
			{
				MoveAction* action = new MoveAction(uid, x, y, MoveRight);
				m_action_list->push_back(action);
				m_engine->getPlayer(player).addMove(uid, x, y, MoveRight);
				x = x - 1;
				LOG(DEBUG) << "Right";
			}
		}
		if (y > 0)
		{
			if (mapCharacter[uid][x][y - 1] > mapCharacter[uid][x][y])
			{
				MoveAction* action = new MoveAction(uid, x, y, MoveBackward);
				m_action_list->push_back(action);
				m_engine->getPlayer(player).addMove(uid, x, y, MoveBackward);
				y = y - 1;
				LOG(DEBUG) << "BackWard";
			}
		}
		if (x < WIDTH - 1)
		{
			if (mapCharacter[uid][x + 1][y] > mapCharacter[uid][x][y])
			{
				MoveAction* action = new MoveAction(uid, x, y, MoveLeft);
				m_action_list->push_back(action);
				m_engine->getPlayer(player).addMove(uid, x, y, MoveLeft);
				x = x + 1;
				LOG(DEBUG) << "Left";
			}
		}
		if (y < HEIGHT - 1)
		{
			if (mapCharacter[uid][x][y + 1] > mapCharacter[uid][x][y])
			{
				MoveAction* action = new MoveAction(uid, x, y, MoveForward);
				m_action_list->push_back(action);
				m_engine->getPlayer(player).addMove(uid, x, y, MoveForward);
				y = y + 1;
				LOG(DEBUG) << "ForWard";
			}
		}
		if (mapCharacter[uid][x][y] == state->getAttribute("move", uid))
		{
			LOG(DEBUG) << "found";
			return true;
		}
	}
	return false;
}

bool Ruler::checkAttack(Etat* state, int uid1, int uid2, int player)
{
	if (m_engine->getPlayer(player).hasAttacked(uid1)) return false;

	int x = state->getAttribute("posX", uid1) - state->getAttribute("posX", uid2);
	int y = state->getAttribute("posY", uid1) - state->getAttribute("posY", uid2);

	if (x < 0) x = -x;
	if (y < 0) y = -y;

	if (state->getAttribute("currentHealth", uid2))
	{
		return x + y <= state->getAttribute("range", uid1);
	}

	return false;
}

bool Ruler::createAttack(Etat * state, int uid1, int uid2)
{
	int power = state->getAttribute("power", uid1);
	power = power - state->getAttribute("defence", uid2);
	if (power < 1) power = 1;

	DamageAction* action = new DamageAction(uid2, power);
	m_action_list->push_back(action);

	if (state->getAttribute("currentHealth", uid2) - power <= 0)
	{
		ElementList* liste = state->getList();
		//liste->erase(uid2);
		//m_engine->getPlayer(liste[liste->findUid(uid2)]->getOwner());

	}

	LOG(DEBUG)<< "Attack succeded from " << uid1 << " to " << uid2 << " for " << power << " damages";

	return true;
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

	ElementList* liste = state->getList();
	LOG(DEBUG) << state->getSize();
	for (int i = 0; i < state->getSize(); i++)
	{
		if((*liste)[i]->getKey() != "VOID_1") map[(*liste)[i]->getX()][(*liste)[i]->getY()] = (*liste)[i]->getD();
	}
}

void Ruler::createMapCharacter(Etat * state, int uid)
{
	int i,j;
		mapCharacter[uid].resize(WIDTH);
		for (int i = 0; i < WIDTH; ++i)
			mapCharacter[uid][i].resize(HEIGHT);

		for (i = 0; i < WIDTH; i++)
			for (j = 0; j < HEIGHT; j++) {
				mapCharacter[uid][i][j] = 0;
			}
}

void Ruler::propagate(int posX, int posY, int value, int uid)
{
	
	mapCharacter[uid][posX][posY] = value;
	if (value > 1) {
		if(posX > 0)
			if (map[posX - 1][posY] < 1 && mapCharacter[uid][posX - 1][posY] < value) propagate(posX - 1, posY, value - 1, uid);
		if(posY > 0)
			if (map[posX][posY - 1] < 1 && mapCharacter[uid][posX][posY - 1] < value) propagate(posX, posY - 1, value - 1, uid);
		if (posY < HEIGHT - 1)
			if (map[posX][posY + 1] < 1 && mapCharacter[uid][posX][posY + 1] < value) propagate(posX, posY + 1, value - 1, uid);
		if (posX < WIDTH - 1)
			if (map[posX + 1][posY] < 1 && mapCharacter[uid][posX + 1][posY] < value) propagate(posX + 1, posY, value - 1, uid);
	}
}

void Ruler::nextPlayer(int played, int toPlay, Etat* state)
{
	if (played != 0)
	{
		m_engine->getPlayer(played).resetMoves();
		m_engine->getPlayer(played).resetAttacks();
	} 
	createMap(state);
	if (m_engine->getPlayer(toPlay).numberPersos() <= 0) return;

	int i;

	for (i = 0; i < m_engine->getPlayer(toPlay).numberPersos(); i++)
	{
		int id = m_engine->getPlayer(toPlay)[i];
		createMapCharacter(state, id);
		LOG(DEBUG) << "propagate begin with X:" << state->getAttribute("posX", id) << " Y:" << state->getAttribute("posY", id) << " and move : " << state->getAttribute("move", id);
		propagate(state->getAttribute("posX", id), state->getAttribute("posY", id), state->getAttribute("move", id), id);
		LOG(DEBUG) << "propagate done";
	}
}

int Ruler::getMapValue(int x, int y, int uid)
{
	return mapCharacter[uid][x][y];
}

std::vector<std::vector<int>> Ruler::getMap(int uid)
{
	return mapCharacter[uid];
}

void Ruler::checkRule(Etat * state)
{
	ElementList* liste = state->getList();
	int i;

	for (i = 0; i < liste->size(); i++)
	{
		if ((*liste)[i]->getD() >= 3)
		{
			int test = (*liste)[i]->getUid();
			if ((*liste)[i]->getAttribute("currentHealth") <= 0 && (*liste)[i]->getAttribute("status") >= 0)
			{
				if ((*liste)[i])
				{

				}
				DeadAction* actionD =new  DeadAction(test);
				m_engine->death(test);
				m_action_list->push_back(actionD);
				update();
			}
		}
	}
}
