#pragma once
#include "Action.hpp"

class EndGameAction : public Action
{
private:
	int m_score;

public:
	EndGameAction(int score);
	~EndGameAction();
	virtual void execute(Etat& e) override;
};
