#include "DamageAction.hpp"

void DamageAction::execute(Etat* state)
{
	value = state->getAttribute("santeCourante", uid) - value;
	if (value < 0 ) value = 0;
	state->setAttribute("santeCourante",value,uid);
}
