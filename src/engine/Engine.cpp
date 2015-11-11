#include "Engine.hpp"

Engine::Engine()
{
	state.reset(new Etat);
	m_ruler.reset(new Ruler(*state));
	
}

void Engine::handleCommand(Command* com)
{
	switch(com->type)
		case Move:
			m_ruler->execute(com, state.get());
}

void Engine::run()
{
	while (1) {

		/*if (liste.size != 0)
		{
			rule.execute(liste[0], state);
			liste.remove[0];
		}*/
	}
}

Etat& Engine::getState()
{
	return *state;
}
