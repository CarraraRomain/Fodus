#include "EndTurnCommand.hpp"

using namespace engine;

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

Command *EndTurnCommand::clone() {
	return new EndTurnCommand(*this);
}

EndTurnCommand::EndTurnCommand():  Command(nullptr, EndTurn)
{

}
