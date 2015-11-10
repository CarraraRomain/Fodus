#include "ModeCommand.hpp"



ModeCommand::ModeCommand(CommandReceiver* receiver, std::string m) : Command(receiver, Mode)
{
	
	mode = m;
}

ModeCommand::~ModeCommand()
{
}

void ModeCommand::execute()
{
	m_command_receiver->handleCommand(this);
}