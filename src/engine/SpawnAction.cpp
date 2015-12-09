#include "SpawnAction.hpp"

using namespace engine;

SpawnAction::SpawnAction(state::Perso * newPerso) : Action(Spawn)
{
	persoSpawned = newPerso;
}

SpawnAction::~SpawnAction()
{
}

void SpawnAction::execute(state::Etat & state)
{
	state.getList()->push_back(persoSpawned);
}
