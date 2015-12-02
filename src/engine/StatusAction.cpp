#include "StatusAction.hpp"



StatusAction::StatusAction(int target, int type) : Action(Status)
{
	uid = target;
	value = type;
}


StatusAction::~StatusAction()
{
}

void StatusAction::execute(Etat & state)
{
	state.getList()->setAttribute("status",value,uid);
}
