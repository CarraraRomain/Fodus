#pragma once

#include "../global.hpp"

class Command
{
public:
	Command();
	virtual ~Command();
	virtual void execute() = 0;
	void setPayload(std::unique_ptr<rapidjson::Document>);
	const rapidjson::Document& getPayload() const;
	const CommandType type = Abstract;
private:
	std::unique_ptr<rapidjson::Document> m_payload;
};



