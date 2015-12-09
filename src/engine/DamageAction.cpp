#include "DamageAction.hpp"

void DamageAction::execute(Etat& state)
{
	if (state.getList()->findUid(uid) == -1) return;
	int currentHealth = state.getAttribute("currentHealth", uid);
	damage = currentHealth - damage;
	if (damage < 0) damage = 0;
	if (damage > currentHealth) damage = currentHealth;
	state.setAttribute("currentHealth", damage, uid);
}

DamageAction::DamageAction(int newUid, int value) 
	: Action(Damage)
{
	uid = newUid;
	damage = value;
}

DamageAction::~DamageAction()
{
}
