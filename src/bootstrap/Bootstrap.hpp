#pragma once



#include <map>
#include "../global.hpp"


/**
 * Class to bootstrap the program
 */
class Bootstrap
{
public:
	Bootstrap(int argc, char** argv);
	~Bootstrap();
	void loadConf();
	void start();
	void run();
	void getConfig(const std::string&) const;
	std::shared_ptr<rapidjson::Document> getDocument(const std::string&);
	void saveDocument(const std::string&, const rapidjson::Document&);

private:
	int m_argc;
	char** m_argv;
	rapidjson::Document m_config;
	// rapidjson doc is not movable nor copyable, we need ptr
	std::map < std::string, std::shared_ptr<rapidjson::Document>> m_docs;
	void Bootstrap::loadFile(const std::string& name);
	bool checkNode(std::string);
	void launch_editor();
	void launch_game();
};

