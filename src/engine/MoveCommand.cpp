#include "MoveCommand.h"

MoveCommand::MoveCommand(CommandReceiver * receiver, int x , int y , AnimationType type, int uid) : Command(receiver, Move)
{
	posX = x;
	posY = y;
	Uid = uid;
	dir = type;
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::execute()
{
	LOG(DEBUG) << "Exec Move";
	m_command_receiver->handleCommand(this);
}
