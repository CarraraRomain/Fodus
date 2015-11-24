#pragma once



#include <map>
#include "../global.hpp"

#include "../engine/DebugCommand.hpp"
#include "../engine/ModeCommand.hpp"

/**
 * Class to bootstrap the program
 */
class Bootstrap: public CommandReceiver
{
public:
	void handleCommand(Command*) override;
	Bootstrap(int argc, char** argv);
	Bootstrap();
	~Bootstrap();
	void loadConf();
	void loadLevelIndex();
	void start();
	void listLevels();
	std::string chooseLevel();
	void run();
	void poolCommands();
	void getConfig(const std::string&) const;
	std::shared_ptr<rapidjson::Document> getDocument(const std::string&);
	void saveDocument(const std::string&, const rapidjson::Document&);
	std::shared_ptr<rapidjson::Document> getLevel(const std::string&);
	std::string getPath(const std::string&);

private:
	int m_argc;
	char** m_argv;
	rapidjson::Document m_config;
	// rapidjson doc is not movable nor copyable, we need ptr
	std::map < std::string, std::shared_ptr<rapidjson::Document>> m_docs;
	std::map < std::string, std::shared_ptr<rapidjson::Document>> m_levels;
	void loadFile(const std::string& name);
	void loadLevel(const std::string& name);
	bool checkNode(const std::string&) const;
	bool checkLevelNode(const std::string&);
	void launch_editor();
	void launch_game();
};