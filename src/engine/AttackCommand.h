#pragma once
#include "Command.hpp"

class AttackCommand : public Command
{
public:
	AttackCommand(CommandReceiver* receiver, int a, int b);
	~AttackCommand();
	virtual void execute() override;

	
	int uid1;
	int uid2;
};