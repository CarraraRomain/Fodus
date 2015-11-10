#pragma once
#include "Action.hpp"

class DamageAction : public Action
{
private:
	int uid;
	int value;

public:
	void execute(Etat* state);
};