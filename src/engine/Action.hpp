#pragma once

#include "../state/Etat.hpp"
#include "../Enum.h"
#include "../global.hpp"

class Action
{
public:
	virtual ~Action();
	CommandType type = Abstract;
	virtual void execute(Etat& e) = 0;
	Action(CommandType type) : type(type) {}
};

