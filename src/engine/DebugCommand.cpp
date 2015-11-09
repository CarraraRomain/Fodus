#include "DebugCommand.hpp"



DebugCommand::DebugCommand()
{
}


DebugCommand::~DebugCommand()
{
}

void DebugCommand::execute()
{
	LOG(DEBUG) << "Command executed";
}
