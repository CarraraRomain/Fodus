#include "AttackCommand.h"

AttackCommand::AttackCommand(CommandReceiver * receiver, int a, int b, int player):Command(receiver, Attack, player)
{
	uid1 = a;
	uid2 = b;
}

AttackCommand::~AttackCommand()
{
}

void AttackCommand::execute()
{
	LOG(DEBUG) << "Exec Attack";
	m_command_receiver->handleCommand(this);
}
