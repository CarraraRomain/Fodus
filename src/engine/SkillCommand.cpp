#include "SkillCommand.hpp"

SkillCommand::SkillCommand(CommandReceiver * receiver, int x, int y, int newuid, int skill, int player) :Command(receiver, Skill, player)
{
	uid = newuid;
	posX = x;
	posY = y;
	skillIndex = skill;
}

SkillCommand::~SkillCommand()
{
}

void SkillCommand::execute()
{
	LOG(DEBUG) << "Exec Skill";
	m_command_receiver->handleCommand(this);
}
