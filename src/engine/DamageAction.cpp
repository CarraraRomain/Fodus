#include "DamageAction.hpp"

/*void DamageAction::execute(Etat* state)
{
	value = state->getAttribute("currentHealth", uid) - value;
	if (value < 0 ) value = 0;
	state->setAttribute("currentHealth",value,uid);
}*/

void DamageAction::execute(Etat* state)
{
	power1 = state->getAttribute("power", uid1);
	defence2 = state->getAttribute("defence", uid2);
	currentHealth2 = state->getAttribute("currentHealth", uid2);
	damage = power1 - defence2;
	if (damage > 0) currentHealth2 = currentHealth2 - damage;
	state->setAttribute("currentHealth", currentHealth2, uid2);
}