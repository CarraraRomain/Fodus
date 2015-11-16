#pragma once
class Command;

/**
 * Command Pattern Receiver Interface
 */
class CommandReceiver
{
public:
	CommandReceiver();
	virtual ~CommandReceiver();
	virtual void handleCommand(Command*) = 0;
};

