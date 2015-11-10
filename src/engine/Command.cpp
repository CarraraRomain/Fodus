#include "Command.hpp"



Command::Command()
{
}

Command::~Command()
{
}


void Command::setPayload(std::unique_ptr<rapidjson::Document> payload)
{
	m_payload = std::move(payload);
}

const rapidjson::Document& Command::getPayload() const
{
	return *m_payload;
}