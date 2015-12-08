#include "SpawnAction.hpp"

SpawnAction::SpawnAction(Perso * newPerso) : Action(Spawn)
{
	persoSpawned = newPerso;
}

SpawnAction::~SpawnAction()
{
}

void SpawnAction::execute(Etat & state)
{
	state.getList()->push_back(persoSpawned);
}
