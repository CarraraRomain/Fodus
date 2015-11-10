#include "DebugCommand.hpp"




DebugCommand::DebugCommand(CommandReceiver* receiver, std::string m) : Command(receiver, Debug)
{
}

DebugCommand::~DebugCommand()
{
}

void DebugCommand::execute()
{
	m_command_receiver->handleCommand(this);
}
