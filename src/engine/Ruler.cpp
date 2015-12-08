#include "Ruler.hpp"

#include "Engine.hpp"
#include "../state/ElementList.hpp"


Ruler::Ruler(Engine* e, Etat& state): m_state(state), m_engine(e), m_end(false)
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
		
	case Skill:
		LOG(DEBUG) << "Ruler : exec Skill Command";
		{
			SkillCommand* skill_com = dynamic_cast<SkillCommand*>(com);

			int found;

			if (found = checkSkill(state, skill_com->posX, skill_com->posY, skill_com->uid, skill_com->skillIndex, skill_com->player))
			{
				createSkill(state, skill_com->uid, skill_com->skillIndex, skill_com->posX, skill_com->posY, found);
				success = true;
				m_engine->getPlayer(skill_com->player)[skill_com->uid].attack();
			}
			else LOG(DEBUG) << skill_com->uid << " can't use skill";
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
	LOG(DEBUG) << "check";
	if (mapCharacter[uid][x][y] > 0) return true;
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
				//LOG(DEBUG) << "Right";
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
				//LOG(DEBUG) << "BackWard";
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
				//LOG(DEBUG) << "Left";
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
			//	LOG(DEBUG) << "ForWard";
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

	if (power >= 5) power = 0.8*power + rand() % (power / 5);

	DamageAction* action = new DamageAction(uid2, power);
	m_action_list->push_back(action);

	LOG(DEBUG)<< "Attack succeded from " << uid1 << " to " << uid2 << " for " << power << " damages";

	return true;
}



int Ruler::checkSkill(Etat* state, int posX, int posY, int uid, int skillIndex, int player)
{
	createMap(state);
	if (m_engine->getPlayer(player)[uid].hasAttacked()) return false;

	int found = 0;
	int i;
	ElementList* liste = state->getList();
	Competence* skill = liste->getSkill(uid, skillIndex);

	if (skill == NULL) return false;
	if (skill->cooldown != 0) return false;

	for (i = 0; i < liste->size(); i++) {
		if ((*liste)[i]->getD() == 3)
		{
			if (liste->getAttribute("posX", (*liste)[i]->getUid()) == posX && liste->getAttribute("posY", (*liste)[i]->getUid()) == posY) found = (*liste)[i]->getUid();
		}
	}

	if (skill->target == 0 && (found != 0 || map[posX][posY] != 0)) return false;
	if (found == 0 && skill->target != 0) return false;
	if (liste->getAttribute("side", uid) != liste->getAttribute("side", found) && skill->target == 1) return false;
	if (liste->getAttribute("side", uid) == liste->getAttribute("side", found) && skill->target == 2) return false;

	int x = state->getAttribute("posX", uid) - posX;
	int y = state->getAttribute("posY", uid) - posY;
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	
	if (x + y <= skill->range) return found;
	
	return false;
}

bool Ruler::createSkill(Etat* state, int uid, int index, int posX, int posY, int target)
{
	ElementList* liste = state->getList();
	Competence* skill = liste->getSkill(uid, index);

	skill->used();

	switch (skill->type)
	{
		case Attack:
		{
			int damage = skill->damage * liste->getAttribute("power", uid) / liste->getAttribute("defence", target);
			DamageAction* action = new DamageAction(target, damage);
			m_action_list->push_back(action);
			LOG(DEBUG) << "Attack succeded from " << uid << " to " << target << " for " << damage << " damages";
			break;
		}

		case Fireball:
		{	
			int damage = skill->damage * liste->getAttribute("power", uid) / liste->getAttribute("defence", target);
			if (damage >= 5)damage = 0.8*damage + rand() % (damage / 5);
			DamageAction* action = new DamageAction(target, damage);
			StatusAction* actionS = new StatusAction(target, 1);
			m_action_list->push_back(action);
			m_action_list->push_back(actionS);
			LOG(DEBUG) << "Fireball succeded from " << uid << " to " << target << " for " << damage << " damages";
			break;
		}

		case Rejuvenate:
		{
			int restore = skill->damage * 0.02 * liste->getAttribute("power", uid);
			if (restore >= 5) restore = 0.8 * restore + rand() % (restore / 5);
			RestoreAction* actionR = new RestoreAction(target, restore);
			m_action_list->push_back(actionR);
			LOG(DEBUG) << "Rejuvenate succeded from " << uid << " to " << target << " for " << restore << " points";
			break;
		}

		case Spawn:
		{
			Perso* zombie = new Perso(*zombie);
			zombie->setClass(Zombie);
			zombie->setAttribute("posX", posX);
			zombie->setAttribute("posY", posY);
			zombie->setAttribute("direction", MoveForward);
			zombie->setAttribute("health", 500);
			zombie->setAttribute("defence", 10);
			zombie->setAttribute("power", 10);
			SpawnAction* actionZ = new SpawnAction(zombie);
			m_action_list->push_back(actionZ);
			LOG(DEBUG) << "Spawn zombie succeded at (" << posX << ", " << posY << ")";
			break;		
		}
	}

return false;
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
		if ((*liste)[i]->getKey() != "VOID_1") map[(*liste)[i]->getX()][(*liste)[i]->getY()] = (*liste)[i]->getD();
	}
}

void Ruler::createMapCharacter(int uid)
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
		EndTurnRule(played, state);
	} 
	createMap(state);
	if (m_engine->getPlayer(toPlay).numberPersos() <= 0) return;

	int i;

	for (auto const &ch: m_engine->getPlayer(toPlay))
	{
		int id = ch.second->UID;
		createMapCharacter(id);
		if(state->getAttribute("posX", id) > 0 && state->getAttribute("posX", id) < WIDTH && state->getAttribute("posY", id)>0 && state->getAttribute("posY", id) < HEIGHT)
			propagate(state->getAttribute("posX", id), state->getAttribute("posY", id), state->getAttribute("move", id), id);
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
	if (m_end) return;
	ElementList* liste = state->getList();
	int i;
	for(auto const &pl: m_engine->getPlayers())
	{
		
		int size = pl.second.size();
		if(size == 0 && pl.first == 1)
		{
		
			m_engine->notifyGameEnd(m_engine->getPlayer(1), 0);
			m_end = true;
			return;
		}
		else if(size == 0 && pl.first == 2)
		{
			m_engine->notifyGameEnd(m_engine->getPlayer(1), 42);
			m_end = true;
			return;
		}

	}
	for (i = 0; i < liste->size(); i++)
	{
		if ((*liste)[i]->getD() >= 3)
		{
			int test = (*liste)[i]->getUid();

			if ((*liste)[i]->getAttribute("currentHealth") <= 0 && (*liste)[i]->getAttribute("status") >= 0)
			{
				if ((*liste)[i]->getType() == Principal)
				{
			
					EndGameAction* actionE = new EndGameAction(false);
					m_action_list->push_back(actionE);
					LOG(INFO) << "============ YOU LOST !!! ============ ";
					
				}
				
				DeadAction* actionD =new  DeadAction(test);
				m_engine->death(test);
				m_action_list->push_back(actionD);
			}
		}
	}
	update();
}

void Ruler::EndTurnRule(int played, Etat * state)
{
	int uid,i;
	ElementList* liste = state->getList();

	for (auto const &ch : m_engine->getPlayer(played))
	{
		uid = ch.second->UID;

		if (state->getAttribute("status", uid) == 1)
		{
			int damage = state->getAttribute("health", uid) / 20;
			if (damage < 1) damage = 1;
			DamageAction* action = new DamageAction(uid, damage);
			m_action_list->push_back(action);
			LOG(DEBUG) << "burn for " << uid << ", and for " << damage << " dégâts";
		}

		for (i = 0; i < state->getAttribute("nbrSkill", uid); i++) {
			if((*liste)[liste->findUid(uid)]->getSkill(i)->cooldown > 0) (*liste)[liste->findUid(uid)]->getSkill(i)->cooldown--;
		}
	}
}
