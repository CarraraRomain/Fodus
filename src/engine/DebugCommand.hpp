#pragma once
#include "Command.hpp"
class DebugCommand :
	public Command
{
public:
	DebugCommand(CommandReceiver* receiver, std::string m);
	~DebugCommand();
	virtual void execute() override;
	std::string string;
};

