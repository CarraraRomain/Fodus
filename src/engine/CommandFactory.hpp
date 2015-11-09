#pragma once

#include "../global.hpp"
#include "CommandCreator.hpp"
#include "Command.hpp"

class CommandFactory
{
public:
	CommandFactory();
	~CommandFactory();
	void registerFactory(const std::string& key, CommandCreator* com);

	std::unique_ptr<Command> build(const std::string& key) const;

private:	
	std::map<std::string, CommandCreator*> m_map;
};

extern CommandFactory command_factory;
