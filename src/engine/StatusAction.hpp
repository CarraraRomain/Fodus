#pragma once
#include "Action.hpp"

class StatusAction : public Action
{
private:
	int uid;
	int value;

public:
	StatusAction(int target,int value);
	~StatusAction();
	void execute(Etat& state);
};

