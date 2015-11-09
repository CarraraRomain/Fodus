#pragma once
#include "../global.hpp"
#include "Command.hpp"



class CommandCreator
{
public:
	CommandCreator(const std::string& key);
	virtual std::unique_ptr<Command> create() = 0;
};

template <class T>
class ComFacto : public CommandCreator
{
public:
	ComFacto(const std::string& key) : CommandCreator(key) {}
	std::unique_ptr<Command> create() override
	{
		std::unique_ptr<T> ptr;
		ptr.reset(new T);
		return std::move(ptr);
	}
};
