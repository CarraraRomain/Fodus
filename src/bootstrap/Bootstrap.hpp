#pragma once



#include <map>
#include "../global.hpp"


/**
 * Class to bootstrap the program
 */
class Bootstrap
{
public:
	Bootstrap();
	~Bootstrap();
	void loadConf();
	void start();
	void getConfig(const std::string&) const;
	std::shared_ptr<rapidjson::Document> getDocument(const std::string&);
	void saveDocument(const std::string&, const rapidjson::Document&);

private:

	rapidjson::Document m_config;
	// rapidjson doc is not movable nor copyable, we need ptr
	std::map < std::string, std::shared_ptr<rapidjson::Document>> m_docs;
	void Bootstrap::loadFile(const std::string& name);
	bool checkNode(std::string);
};

