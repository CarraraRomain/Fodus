#include "DeadAction.h"

DeadAction::DeadAction(int newUid) : Action(Dead)
{
	uid = newUid;
}

void DeadAction::execute(Etat& state)
{
	int own = state.getAttribute("owner", uid);
	state.setAttribute("status", -1, uid);
	state.getList()->erase(uid);
	LOG(DEBUG) << uid << " is dead";
}

DeadAction::~DeadAction()
{
}
