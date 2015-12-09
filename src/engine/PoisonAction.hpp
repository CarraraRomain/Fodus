#pragma once
#include "Action.hpp"

class PoisonAction : public Action
{
private:
	int uid;
	int range;
	int limit;
	int turn;

public:
	virtual void execute(Etat& state) override;
	PoisonAction(int uid, int limit, int turn);
	~PoisonAction();
};