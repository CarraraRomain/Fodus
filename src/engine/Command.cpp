#include "Command.hpp"

using namespace engine;

Command::~Command()
{
}

Command::Command(CommandReceiver* command_receiver, CommandType type, int player)
: type(type), player(player), m_command_receiver(command_receiver)
{
}