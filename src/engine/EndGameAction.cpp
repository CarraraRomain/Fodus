#include "EndGameAction.hpp"

using namespace engine;

EndGameAction::EndGameAction(int score) : Action(Exit), m_score(score)
{
}

EndGameAction::~EndGameAction()
{
}

void EndGameAction::execute(state::Etat& e)
{
	e.setResult(m_score);
}
