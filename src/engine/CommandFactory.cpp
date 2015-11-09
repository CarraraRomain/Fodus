#include "CommandFactory.hpp"



CommandFactory::CommandFactory()
{
}


CommandFactory::~CommandFactory()
{
}

void CommandFactory::registerFactory(const std::string& key, std::unique_ptr<CommandCreator> com)
{
	m_map[key] = std::move(com);
}

std::unique_ptr<Command> CommandFactory::build(const std::string& key) const
{
	std::map<std::string, std::unique_ptr<CommandCreator>>::const_iterator i;
	i = m_map.find(key);
	if(i!=m_map.end())
	{
		return i->second->create();
	}
	return std::unique_ptr<Command>(nullptr);
}