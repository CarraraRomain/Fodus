#include "RestoreAction.hpp"

void RestoreAction::execute(Etat & state)
{
	restore = state.getAttribute("currentHealth", uid) + restore;
	health = state.getAttribute("health", uid);
	if (restore > health)
		state.setAttribute("currentHealth", health, uid);
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
