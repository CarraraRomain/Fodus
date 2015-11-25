#pragma once
#include "Command.hpp"

class SkillCommand : public Command
{
public:
	SkillCommand(CommandReceiver* receiver, int a, int b, int player);
	~SkillCommand();
	virtual void execute() override;

	int uid1;
	int uid2;
};