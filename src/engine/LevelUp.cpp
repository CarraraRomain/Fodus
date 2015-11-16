#include "LevelUp.h"

void LevelUp::execute(Etat* state)
{
	health = state->getAttribute("health", uid) + 10;
	defence = state->getAttribute("defence", uid) + 5;
	power = state->getAttribute("power", uid) + 10;
	limitZombie = state->getAttribute("limitZombie", uid) + 1;
	level = state->getAttribute("level", uid) + 1;

	state->setAttribute("health", health, uid);
	state->setAttribute("defence", defence, uid);
	state->setAttribute("power", power, uid);
	state->setAttribute("limitZombie", limitZombie, uid);
	state->setAttribute("level", level, uid);	
}
