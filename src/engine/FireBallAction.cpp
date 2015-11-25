#include "FireBallAction.hpp"

void FireBallAction::execute(Etat & state)
{
	// Fireball action: we lose 5 power for making a damage of 10
	power = state.getAttribute("power", uid1) - 5;
	if (power < 0) power = 0;
	state.setAttribute("power", power, uid1);

	currentHealth = state.getAttribute("currentHealth", uid2) - 10;
	if (currentHealth < 0) currentHealth = 0;
	state.setAttribute("currentHealth", currentHealth, uid2);
}

FireBallAction::FireBallAction(int newuid1, int newpower, int newuid2, int newcurrentHealth)
	: Action(FireBall)
{
	uid1 = newuid1;
	power = newpower;
	uid2 = newuid2;
	currentHealth = newcurrentHealth;
}

FireBallAction::~FireBallAction()
{
}
