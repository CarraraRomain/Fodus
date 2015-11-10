#pragma once

#include "../global.hpp"

class Command
{
public:
	// payload is set in the constructor
	Command();
	virtual ~Command();
	virtual void execute() = 0;
	const std::string& getPayload(std::string) const;
	const CommandType type = Abstract;
protected:
	std::map<std::string, std::string> m_payload;
};



