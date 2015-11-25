#pragma once
#include "Action.hpp"

class EndGameAction : public Action
{
private:
	bool result;

public:
	EndGameAction(bool result);
	~EndGameAction();
	virtual void execute(Etat& e) override;
};
