#include "Command.hpp"

using namespace engine;

Command::~Command()
{
}

Command::Command(CommandReceiver* command_receiver, CommandType type, int player=0)
: type(type), player(player), m_command_receiver(command_receiver)
{
}