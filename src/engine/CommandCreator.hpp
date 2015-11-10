#pragma once
#include "../global.hpp"
#include "Command.hpp"

// Avoid circular include
class Bootstrap;

class CommandCreator
{
public:
	virtual ~CommandCreator()
	{
	}

	CommandCreator(Bootstrap* boot, const std::string& key);
	virtual std::unique_ptr<Command> create() = 0;
};

template <class T>
class ComFacto : public CommandCreator
{
public:
	ComFacto(Bootstrap* boot, const std::string& key) : CommandCreator(boot, key) {}
	std::unique_ptr<Command> create() override
	{
		std::unique_ptr<T> ptr;
		ptr.reset(new T);
		return std::move(ptr);
	}

};
