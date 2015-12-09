#include "RestoreAction.hpp"

using namespace engine;

void RestoreAction::execute(Etat & state)
{
	currentHealth = state.getAttribute("currentHealth", uid);
	health = state.getAttribute("health", uid);
	restore = currentHealth + restore;
	if (restore > health) restore = health;
	if (restore < 0) restore = currentHealth;
	state.setAttribute("currentHealth", restore, uid);
}

RestoreAction::RestoreAction(int newUid, int restoreValue)
	: Action(Restore)
{
	uid = newUid;
	restore = restoreValue;
}

RestoreAction::~RestoreAction()
{
}
