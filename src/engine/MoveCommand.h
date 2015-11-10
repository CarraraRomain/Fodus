#pragma once
#include "Command.hpp"

class MoveCommand : public Command
{
public:
	MoveCommand(CommandReceiver* receiver, int x, int y , int uid);
	~MoveCommand();
	virtual void execute() override;
	
	int posX;
	int posY;
	int Uid;
};