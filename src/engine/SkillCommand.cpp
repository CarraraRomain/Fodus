#include "SkillCommand.hpp"

SkillCommand::SkillCommand(CommandReceiver * receiver, int a, int b, int player) :Command(receiver, Attack, player)
{
	uid1 = a;
	uid2 = b;
}

SkillCommand::~SkillCommand()
{
}

void SkillCommand::execute()
{
	LOG(DEBUG) << "Exec Skill";
	m_command_receiver->handleCommand(this);
}
