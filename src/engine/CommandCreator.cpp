#include "CommandCreator.hpp"

// Avoid circular include
// (not to put in the .hpp)
#include "../bootstrap/Bootstrap.hpp"


CommandCreator::CommandCreator(Bootstrap* boot, const std::string& key)
{
	boot->command_factory.registerFactory(key, this);
}