#include "CommandCreator.hpp"

#include "CommandFactory.hpp"


CommandCreator::CommandCreator(const std::string& key)
{
	command_factory.registerFactory(key, this);
}