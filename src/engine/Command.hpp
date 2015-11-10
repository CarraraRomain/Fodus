#pragma once

#include "../global.hpp"
#include "CommandReceiver.hpp"

class Command
{
public:
	Command(CommandReceiver* command_receiver, CommandType type)
		: type(type), m_command_receiver(command_receiver)
	{
	}
	virtual ~Command();
	virtual void execute() = 0;
	const CommandType type = Abstract;
protected:
	CommandReceiver* m_command_receiver;
};



