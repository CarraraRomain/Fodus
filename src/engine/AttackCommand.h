#pragma once
#include "Command.hpp"

class AttackCommand : public Command
{
public:
	AttackCommand(CommandReceiver* receiver, int a, int b, int player);
	~AttackCommand();
	virtual void execute() override;

	
	int uid1;
	int uid2;
};