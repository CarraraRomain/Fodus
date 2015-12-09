#include "MoveCommand.hpp"

using namespace engine;

MoveCommand::MoveCommand(CommandReceiver * receiver, int x , int y , AnimationType type, int uid, int player) : Command(receiver, Move, player)
{
	posX = x;
	posY = y;
	Uid = uid;
	dir = type;
}

MoveCommand::~MoveCommand()
{
}

/**
 * Command pattern exec method
 */
void MoveCommand::execute()
{
	LOG(DEBUG) << "Exec Move";
	m_command_receiver->handleCommand(this);
}
