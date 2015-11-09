#pragma once
#include "Command.hpp"
#include "../global.hpp"

class CommandFactory
{
public:
	CommandFactory();
	~CommandFactory();
	void registerFactory(const std::string& key, std::unique_ptr<CommandCreator> com);

	std::unique_ptr<Command> build(const std::string& key) const;

private:	
	std::map<std::string, std::unique_ptr<CommandCreator>> m_map;
};

