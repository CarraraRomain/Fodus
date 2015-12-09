#include "Engine.hpp"
#include "EndTurnCommand.hpp"
#include "../state/Case.hpp"

Engine::Engine(Bootstrap* boot): m_boot(boot)
{
	state.reset(new Etat(0));
	m_ruler.reset(new Ruler(this,*state));
	m_ruler->createMap(state.get());
}

void Engine::loadLevel(const std::string level)
{
	LOG(DEBUG) << "Loading level " << level << std::endl;
	// loading a level from ../../res/GFX/level.json
	std::shared_ptr<rapidjson::Document> doc;
	try
	{
		doc = m_boot->getLevel(level);
	}
	catch (std::invalid_argument e) 
	{
		LOG(FATAL) << e.what();
	}
	LOG(DEBUG) << "Done";

	//std::cout << level["header"].GetString();
	//cout << level["level"][0][0][0..Depth]["key"].GetString();

	const rapidjson::Value& b = (*doc)["level"];
	int posX = 0;
	for (rapidjson::SizeType i = 0; i < b.Size(); i++)
	{
		const rapidjson::Value& c = b[i];
		//cout << c[0][0..Depth]["key"].GetString();

		for (rapidjson::SizeType j = 0; j < c.Size(); j++)
		{
			// X = j | Y = i
			// e : [0..Depth]["key"]
			const rapidjson::Value& e = c[j];

			for (rapidjson::SizeType k = 0; k < e.Size(); k++) {
				Case* ptr_case = new Case(rand());
				ptr_case->setKey(e[k]["key"].GetString());
				ptr_case->setX(posX);
				ptr_case->setY(i);
				ptr_case->setD(k);
				state->getList()->push_back(ptr_case);
			}
			posX++;
		}
		posX = 0;
	}

	LOG(DEBUG) << "Load OK";
}

/**
 * Command pattern receiver method
 */
void Engine::handleCommand(Command* com)
{
	try {
		switch (com->type)
		{
		case Move:
			m_ruler->execute(com, state.get());
			break;
		case Attack:
			m_ruler->execute(com, state.get());
			break;
		case Skill:
			m_ruler->execute(com, state.get());
			break;
		case EndTurn:
			nextPlayer(dynamic_cast<EndTurnCommand*>(com)->m_player);
			break;
		}
		//state->notify();
		LOG(DEBUG) << "Notify : Global";
		notifyGlobal();
	} catch (std::logic_error e)
	{
		LOG(DEBUG) << e.what();
	}
	
}

/**
 * Main entry point
 */
void Engine::run()
{
	m_ruler->checkRule(state.get());
}

bool Engine::hasPlayed(int player)
{
	for(auto pl: m_has_played)
	{
		if (player == pl) return true;
	}
	return false;
}

Etat& Engine::getState()
{
	return *state;
}

int Engine::registerPlayer(int player, EngineObserver* obs)
{
	if (obs == nullptr) return 403;
	for(auto i : m_players_obs)
	{
		if (i.first == player) return 400;
	}
	m_players_obs[player] = obs;
//	m_players[player] = Player(player);
	return 1;
}

int Engine::connect(int client)
{
	if (client == 0) return 403;
	m_clients.push_back(client);
	return 1;
}

void Engine::start()
{
	//TestGame::test_load_elt_list(state->getList(), m_boot);
	m_players.erase(0);
	// Quick and dirty addition of a perso
	Perso* elt = new Perso(1, 1);
	elt->setAttribute("move", 10);
	elt->setX(17);
	elt->setY(10);
	elt->setD(3);
	elt->setKey("MLP");
	elt->setAttribute("currentHealth", 100);
	elt->setAttribute("power", 100);
	elt->setAttribute("defence", 85);
	elt->setAttribute("side", 1);
	elt->setAttribute("status", 0);
	state->getList()->push_back(elt);

	Competence* attack = new Competence(Attack, 10, 2, 1, 2, 0);
	elt->addSkill(attack);
	Competence* fireball = new Competence(Fireball,20, 3, 2, 10, 3);
	elt->addSkill(fireball);
	Competence* spawnZ = new Competence(ZombieSpawn, 20, 0, 1, 3, 0);
	elt->addSkill(spawnZ);
	Competence* heal = new Competence(Rejuvenate, 20, 3, 1, 15, 3);
	elt->addSkill(heal);

	// Elt index is size-1
	m_players[1] = Player(1,0);
	m_players[1].addOwnedPerso(elt->getUid());

	Perso* foe = new Perso(89, 2);
	foe->setClass(Monstre);
	foe->setAttribute("move", 5);
	foe->setAttribute("range", 1);
	foe->setX(12);
	foe->setY(5);
	foe->setD(3);
	foe->setKey("FOE");
	foe->setAttribute("health", 100);
	foe->setAttribute("currentHealth", 100);
	foe->setAttribute("defence", 85);
	foe->setAttribute("status",0);
	foe->setAttribute("side", 2);
	state->getList()->push_back(foe);

	Competence* attack2 = new Competence(Attack, 10, 2, 1, 1, 0);
	foe->addSkill(attack2);
	Competence* heal2 = new Competence(Rejuvenate, 20, 1, 1, 0, 3, rand()%4);
	foe->addSkill(heal2);
	Competence* fireball2 = new Competence(Fireball, 20, 2, 1, 10, 3, rand()%4);
	foe->addSkill(fireball2);
	
	Perso* foe2 = new Perso(55, 2);
	foe2->setClass(Monstre);
	foe2->setAttribute("move", 5);
	foe2->setAttribute("range", 1);
	foe2->setX(5);
	foe2->setY(5);
	foe2->setD(3);
	foe2->setKey("FOE");
	foe2->setAttribute("health", 100);
	foe2->setAttribute("currentHealth", 100);
	foe2->setAttribute("defence", 85);
	foe2->setAttribute("status", 0);
	foe2->setAttribute("side", 2);
	state->getList()->push_back(foe2);

	Competence* attack3 = new Competence(Attack, 10, 2, 1, 1, 0);
	foe2->addSkill(attack3);
	Competence* heal3 = new Competence(Rejuvenate, 20, 1, 1, 0, 3, rand()%4);
	foe2->addSkill(heal3);
	Competence* fireball3 = new Competence(Fireball, 20, 2, 1, 10, 3, rand()%4);
	foe2->addSkill(fireball3);	

	//m_players[0] = Player(1, 1);
	m_players[2] = Player(89, 1);
	m_players[2].addOwnedPerso(foe->getUid());

	//[3] = Player(3, 1);
	m_players[2].addOwnedPerso(foe2->getUid());

	

	nextPlayer(0);


}

Player& Engine::getPlayer(int id)
{
	return m_players[id];
}

std::map<int, Player>& Engine::getPlayers()
{
	return m_players;
}

int Engine::getMapValue(int x, int y, int uid)
{
	return m_ruler->getMapValue(x, y, uid);;
}

std::vector<std::vector<int>> Engine::getMap(int uid)
{
	
	return m_ruler->getMap(uid);
}

void Engine::death(int uid)
{
	int own = state->getAttribute("owner", uid);
	m_players[own].removePerso(uid);
}

void Engine::propagate(int x, int y, int valeur, int uid)
{
	m_ruler->createMap(state.get());
	m_ruler->createMapCharacter(uid);
	m_ruler->propagate(x, y, valeur, uid);
}

ElementList Engine::syncRequest()
{
	ElementList list = *(state->getList());
	return list;
}

void Engine::syncFull(int pid)
{
	notifySingle(pid);
}

int Engine::whoIsPlaying()
{
	return m_player_playing;
}

int Engine::registerPlayer(int player)
{
	m_clients_players[0] = player;
	return 1;
}

int Engine::getCurrentPlayer()
{
	return current_player_uid;
}

void Engine::nextPlayer(int played)
{
	int toPlay;
	if(played != 0) m_has_played.push_back(played);
	if (played == 0) nextTurn();
	if (m_players.size() <= m_has_played.size()) {
		m_has_played.clear();
		toPlay = 1;
		LOG(DEBUG) << "Next turn";
		nextTurn();
	}
	else toPlay = played + 1;

	if (toPlay > m_players.size()) toPlay = 1;
	current_player_uid = toPlay;
	LOG(DEBUG) << "played : " << played << "     toPlay : " << toPlay;

	LOG(DEBUG) << "=== TURN " << state->getTurn() << " Player :" << current_player_uid << " ===";

	m_ruler->nextPlayer(played, toPlay, state.get());

	notifyNowPlaying(toPlay);
	notifyCanPlay(toPlay);
}

void Engine::nextTurn()
{
	state->nextTurn();
}