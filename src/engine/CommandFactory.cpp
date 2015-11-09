#include "CommandFactory.hpp"




CommandFactory::CommandFactory()
{
}


CommandFactory::~CommandFactory()
{
}

void CommandFactory::registerFactory(const std::string& key, CommandCreator* com)
{
	m_map[key] = com;
}

std::unique_ptr<Command> CommandFactory::build(const std::string& key) const
{
	std::map<std::string, CommandCreator*>::const_iterator i;
	i = m_map.find(key);
	if(i!=m_map.end())
	{
		return i->second->create();
	}
	return std::unique_ptr<Command>(nullptr);
}
