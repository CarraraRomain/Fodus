#pragma once
#include "Action.hpp"
#include <vector>

class ActionList
{
private:
	std::vector<std::unique_ptr<Action>> liste;
	Etat state;

public:
	void ajout(std::unique_ptr<Action> newAction);
};