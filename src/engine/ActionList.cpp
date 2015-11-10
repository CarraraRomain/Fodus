#include "ActionList.hpp"

void ActionList::ajout(std::unique_ptr<Action> newAction)
{
	liste.push_back(std::move(newAction));
}
