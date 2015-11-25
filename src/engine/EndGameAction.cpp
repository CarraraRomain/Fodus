#include "EndGameAction.hpp"

EndGameAction::EndGameAction(bool newResult) : Action(Exit)
{
	result = newResult;
}

EndGameAction::~EndGameAction()
{
}

void EndGameAction::execute(Etat& e)
{
	e.setResult(result);
}
