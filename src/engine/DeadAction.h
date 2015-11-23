#pragma once
#include "Action.hpp"

class DeadAction : public Action
{
private:
	int uid;
	int value;

public:
	DeadAction(int newUid);
	virtual void execute(Etat& state) override;
	virtual ~DeadAction();
};