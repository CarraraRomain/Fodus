#pragma once
#include "Command.hpp"

class MoveCommand : public Command
{
public :
	MoveCommand();
	virtual ~MoveCommand();

private:
	CommandType type;
};