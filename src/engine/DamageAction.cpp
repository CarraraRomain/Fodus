#include "DamageAction.hpp"

void DamageAction::execute(Etat* state)
{
	damage = state->getAttribute("currentHealth", uid1) - damage;
	if (damage < 0 ) damage = 0;
	state->setAttribute("currentHealth",damage,uid2);
}

DamageAction::DamageAction(int newUid1, int newUid2, int value) 
	: Action(Damage)
{
	uid1 = newUid1;
	uid2 = newUid2;
	damage = value;
}

DamageAction::~DamageAction()
{
}
