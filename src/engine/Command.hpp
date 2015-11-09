#pragma once

#include "../global.hpp"

class Command
{
public:
	Command();
	virtual ~Command();
	virtual void execute() = 0;
};



