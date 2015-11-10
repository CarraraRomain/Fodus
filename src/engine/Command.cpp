#include "Command.hpp"



Command::Command()
{
}

Command::~Command()
{
}

const std::string& Command::getPayload(std::string needle) const
{
	std::map<std::string, std::string>::const_iterator it = m_payload.find(needle);
	if (it != m_payload.end())
	{
		//element found;
		return it->second;
	}
	return "";
}
