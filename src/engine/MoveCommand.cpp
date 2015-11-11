#include "MoveCommand.h"

MoveCommand::MoveCommand(CommandReceiver * receiver, int x , int y , int uid) : Command(receiver, Move)
{
	posX = x;
	posY = y;
	Uid = uid;
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::execute()
{
	LOG(DEBUG) << "Exec Move";
	m_command_receiver->handleCommand(this);
}
