#include "PoisonAction.hpp"

void PoisonAction::execute(Etat& state)
{
	if (state.getList()->findUid(uid) == -1) return;
	range = state.getAttribute("range", uid);
	limit = range - limit;
	if (limit < 0) limit = 0;
	if (limit > range) limit = range;
	if (turn > 0)
	{
		state.setAttribute("range", limit, uid);
	}
	else
	{
		state.setAttribute("range", range, uid);
	}
}

PoisonAction::PoisonAction(int newUid, int newLimit, int newTurn)
	: Action(Poison)
{
	uid = newUid;
	limit = newLimit;
	turn = newTurn;	
}

PoisonAction::~PoisonAction(){}
