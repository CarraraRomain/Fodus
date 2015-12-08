#include "DamageAction.hpp"

void DamageAction::execute(Etat& state)
{
	if (state.getList()->findUid(uid) == -1) return;
	damage = state.getAttribute("currentHealth", uid) - damage;
	if (damage < 0 ) damage = 0;
	state.setAttribute("currentHealth",damage,uid);
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
