#include "ModeCommand.hpp"

using namespace engine;

ModeCommand::ModeCommand(CommandReceiver* receiver, std::string m) : Command(receiver, Mode)
{
	
	mode = m;
}

ModeCommand::~ModeCommand()
{
}

/**
 * Command pattern exec method
 */
void ModeCommand::execute()
{
	m_command_receiver->handleCommand(this);
}