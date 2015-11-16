#include "DeadAction.h"

void DeadAction::execute(Etat* state)
{
	value = state->getAttribute("currentHealth", uid);
	if (value <= 0)
	{
		state->setAttribute("status", -1, uid);
		LOG(DEBUG) << uid << "is dead";
	}
}
