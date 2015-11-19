#include "Engine.hpp"
#include "EndTurnCommand.hpp"

Engine::Engine(Bootstrap* boot): m_boot(boot)
{
	state.reset(new Etat(0));
	m_ruler.reset(new Ruler(this,*state));
	m_ruler->createMap(state.get());
}
/**
 * Command pattern receiver method
 */
void Engine::handleCommand(Command* com)
{
	switch (com->type)
	{
	case Move:
		m_ruler->execute(com, state.get());
		break;
	case Attack:
		m_ruler->execute(com, state.get());
		break;
	case EndTurn:
		nextPlayer(dynamic_cast<EndTurnCommand*>(com)->m_player);
		break;
	}
	state->notify();
}

/**
 * Main entry point
 */
void Engine::run()
{
		/*if (liste.size != 0)
		{
			rule.execute(liste[0], state);
			liste.remove[0];
		}*/

}

Etat& Engine::getState()
{
	return *state;
}

int Engine::registerPlayer(int client, int player)
{
	if (client == 0) return 403;
	for(auto i : m_clients_players)
	{
		if (i.second == player) return 400;
	}
	m_clients_players[client] = player;
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
	TestGame::test_load_elt_list(state->getList(), m_boot);
	m_players.erase(0);
	// Quick and dirty addition of a perso
	Perso* elt = new Perso(1, 1);
	elt->setAttribute("move", 10);
	elt->setX(16);
	elt->setY(10);
	elt->setD(3);
	elt->setKey("MLP");
	state->getList()->push_back(elt);
	// Elt index is size-1
	m_players[1] = Player(1);
	m_players[1].addOwnedPerso(state->getList()->size() - 1);

	Perso* foe = new Perso(89, 2);
	foe->setAttribute("move", 3);
	foe->setX(8);
	foe->setY(7);
	foe->setD(3);
	foe->setKey("FOE");
	state->getList()->push_back(foe);
	
	m_players[2] = Player(89);
	m_players[2].addOwnedPerso(state->getList()->size() - 1);
	nextPlayer(0);
}

Player& Engine::getPlayer(int id)
{
	return m_players[id];
}

std::map<int, Player> Engine::getPlayers() const
{
	return m_players;
}

int Engine::registerPlayer(int player)
{
	m_clients_players[0] = player;
	return 1;
}

void Engine::nextPlayer(int played)
{
	int toPlay;
	if(played != 0) m_has_played.push_back(played);
	if (m_players.size() == m_has_played.size()) {
		m_has_played.clear();
		toPlay = 1;
		LOG(DEBUG) << "Next turn";
		nextTurn();
	}
	else toPlay = played + 1;

	if (toPlay >= m_players.size()) toPlay = 1;

	m_ruler->nextPlayer(played, toPlay, state.get());

}

void Engine::nextTurn()
{
	state->nextTurn();
}