#pragma once
#include "Command.hpp"
class DebugCommand :
	public Command
{
public:
	DebugCommand();
	~DebugCommand();
	virtual void execute() override;
};

