#include "Engine.hpp"

Engine::Engine(Bootstrap* boot): m_boot(boot)
{
	state.reset(new Etat(0));
	m_ruler.reset(new Ruler(*state));
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
	case EndTurn:
		state->nextTurn();
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
	// Quick and dirty addition of a perso
	Perso* elt = new Perso(42);
	elt->setAttribute("deplacement", 10);
	elt->setX(16);
	elt->setY(10);
	elt->setD(0);
	elt->setKey("MLP");
	state->getList()->push_back(elt);

}

int Engine::registerPlayer(int player)
{
	m_clients_players[0] = player;
	return 1;
}
