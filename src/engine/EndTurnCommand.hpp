#pragma once
#include "Command.hpp"
class EndTurnCommand : public Command
{
public:
	EndTurnCommand(CommandReceiver* receiver, int player);
	~EndTurnCommand();
	virtual void execute() override;
	int m_player;
};

