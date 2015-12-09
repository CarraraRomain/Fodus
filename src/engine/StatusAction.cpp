#include "StatusAction.hpp"

using namespace engine;

StatusAction::StatusAction(int target, int type) : Action(Status)
{
	uid = target;
	value = type;
}


StatusAction::~StatusAction()
{
}

void StatusAction::execute(state::Etat & state)
{
	if (state.getList()->findUid(uid) == -1) return;
	state.getList()->setAttribute("status",value,uid);
}
