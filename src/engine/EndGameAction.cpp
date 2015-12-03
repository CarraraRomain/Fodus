#include "EndGameAction.hpp"

EndGameAction::EndGameAction(int score) : Action(Exit), m_score(score)
{
}

EndGameAction::~EndGameAction()
{
}

void EndGameAction::execute(Etat& e)
{
	e.setResult(m_score);
}
