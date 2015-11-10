#pragma once
#include "Action.hpp"
#include <vector>

class ActionList
{
private:
	std::vector<Action*> liste;
	Etat state;

public:
	void addition(Action* newAction);
};