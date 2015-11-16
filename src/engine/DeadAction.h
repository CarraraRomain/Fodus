#pragma once
#include "Action.hpp"

class DeadAction : public Action
{
private:
	int uid;
	int value;

public:
	void execute(Etat* state);
};