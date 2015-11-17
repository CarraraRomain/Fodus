#include "EndTurnCommand.hpp"




EndTurnCommand::EndTurnCommand(CommandReceiver* receiver, int player) :
	Command(receiver, EndTurn), m_player(player)
{
}

EndTurnCommand::~EndTurnCommand()
{
}

void EndTurnCommand::execute()
{
	m_command_receiver->handleCommand(this);
}