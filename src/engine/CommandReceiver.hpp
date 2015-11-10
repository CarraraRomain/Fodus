#pragma once
class Command;

class CommandReceiver
{
public:
	CommandReceiver();
	~CommandReceiver();
	virtual void handleCommand(Command*) = 0;
};

