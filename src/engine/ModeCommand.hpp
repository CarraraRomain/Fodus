#pragma once
#include "Command.hpp"

class ModeCommand : public Command 
{
public:
	ModeCommand(CommandReceiver* receiver, std::string m);
	~ModeCommand();
	virtual void execute() override;
	std::string mode;
};

