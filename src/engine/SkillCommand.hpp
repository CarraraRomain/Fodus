#pragma once
#include "Command.hpp"

class SkillCommand : public Command
{
public:
	SkillCommand(CommandReceiver* receiver, int x, int y, int uid, int skillIndex, int player);
	~SkillCommand();
	virtual void execute() override;

	int uid;
	int posX;
	int posY;
	int skillIndex;
};