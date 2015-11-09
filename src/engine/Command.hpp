#pragma once

#include "../global.hpp"

class Command
{
public:
	Command();
	virtual ~Command();
	virtual void execute() = 0;
};


class CommandCreator
{
public:
	virtual std::unique_ptr<Command> create() = 0;
};

template <class T>
class ComFacto: public CommandCreator
{
public:
	virtual std::unique_ptr<Command> create() override
	{
		std::unique_ptr<T> ptr;
		ptr.reset(new T);
 		return std::move(ptr);
	}
};


