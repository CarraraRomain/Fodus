#include "ActionList.hpp"

void ActionList::addition(Action* newAction)
{
	liste.push_back(std::move(newAction));
}
