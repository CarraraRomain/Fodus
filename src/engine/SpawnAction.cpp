#include "SpawnAction.hpp"

SpawnAction::SpawnAction(Perso * newPerso) : Action(Spawn)
{
}

SpawnAction::~SpawnAction()
{
}

void SpawnAction::execute(Etat & state)
{
	state.getList()->push_back(persoSpawned);
}
