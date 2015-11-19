#pragma once

#include "../global.hpp"
#include "CommandReceiver.hpp"

class Command
{
public:
	Command(CommandReceiver* command_receiver, CommandType type, int player=0)
		: type(type), player(player), m_command_receiver(command_receiver)
	{
	}
	virtual ~Command();
	virtual void execute() = 0;
	const CommandType type = Abstract;
	const int player;
protected:
	CommandReceiver* m_command_receiver;
};



