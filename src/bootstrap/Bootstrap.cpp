#include "Bootstrap.hpp"
#include "../editor/Editor.hpp"
#include "../game/Game.hpp"


Bootstrap::Bootstrap(int argc, char** argv)
{
	m_argc = argc;
	m_argv = argv;
}


Bootstrap::~Bootstrap()
{
}

void Bootstrap::loadConf()
{
	LOG(DEBUG) << "Opening global config";
	m_config.SetObject();

	std::stringstream ss;
	std::ifstream ifs;
	ifs.open(GLOBAL_CONF_FILE, std::ios::binary);
	if (ifs.is_open())
	{
		
		ss << ifs.rdbuf(); // 1
		if (m_config.Parse<0>(ss.str().c_str()).HasParseError()) 
			LOG(FATAL) << "JSON bad encoding";
		
	}
	else LOG(FATAL) << "File not found";
	
	ifs.close();
	LOG(DEBUG) << "Loaded global config";
}

void Bootstrap::start()
{
	LOG(DEBUG) << "Bootstrap is starting";
	loadConf();
	
}

void Bootstrap::run()
{
	LOG(DEBUG) << "Bootstrap is running";
	// Launch Args
	// TODO to complete
	std::string type;
	if (m_argc > 1) type = m_argv[1];


	if (type == "editor") launch_editor();
	else if (type == "game") launch_game();
	else {
		do
		{
			std::cout << "> Launch game or level editor? (game/editor) ";
			std::cin >> type;
			if (type == "editor") launch_editor();
			else if (type == "game") launch_game();
		} while (type != "game" && type != "editor");
	}
	LOG(DEBUG) << "Boostrap ended";
}

void Bootstrap::getConfig(const std::string&) const
{
}

std::shared_ptr<rapidjson::Document> Bootstrap::getDocument(const std::string& key)
{
	std::map < std::string, std::shared_ptr<rapidjson::Document>>::const_iterator it;
	rapidjson::Document re;

	it = m_docs.find(key);
	if (it != m_docs.end()) return it->second;
	
	
	loadFile(key);

	return getDocument(key);
	
}

void Bootstrap::loadFile(const std::string& name)
{
	LOG(DEBUG) << "Opening " << name;
	std::shared_ptr<rapidjson::Document> file;
	file.reset(new rapidjson::Document());
	file->SetObject();
	if(!checkNode(name))
	{
		LOG(ERROR) << "Cannot load " << name;
		throw std::invalid_argument("No such res");
	}
	std::string path = m_config["resources"][name].GetString();
	std::stringstream ss;
	std::ifstream ifs;
	ifs.open(path, std::ios::binary);
	if (ifs.is_open())
	{
		ss << ifs.rdbuf();
		if (file->Parse<0>(ss.str().c_str()).HasParseError())
		{
			LOG(ERROR) << "JSON bad encoding";
			throw std::invalid_argument("JSON bad encoding");
		}
			
	}
	else 
	{
		LOG(ERROR) << "File not found";
		throw std::invalid_argument("File not found");
	}
	ifs.close();
	m_docs[name] = std::move(file);
	LOG(DEBUG) << "Loaded " << name;
}

bool Bootstrap::checkNode(std::string name)
{
	if (!m_config["resources"].HasMember(name)) {
		LOG(ERROR) << "Config has no res " << name;
		return false;
	}
	if(!m_config["resources"][name].IsString())
	{
		LOG(ERROR) << name << " node is not a string";
		return false;
	}
	return true;
}



/**
* Launch the editor
*/
void Bootstrap::launch_editor()
{
	LOG(DEBUG) << "Launching Editor";
	bool nerr = true;
	std::string choice;
	std::string name;
	Editor editor(this);
	std::cout << "Level Editor" << std::endl;
	do {
		while (choice != "yes"  && choice != "no")
		{
			std::cout << "\n======================\n";
			std::cout << "New level? (yes/no) ";
			std::cin >> choice;
		}
		// TODO Bootstrap will fetch all level names, awesome
		std::cout << "Level file name? ";
		std::cin >> name;
		editor.setFile(name);
		if (choice == "yes")
		{
			editor.new_level();
		}
		try
		{
			editor.load_level();
			nerr = true;
		}
		catch (const std::invalid_argument & e)
		{
			std::cerr << e.what();
			std::cerr << std::endl;
			nerr = false;
			choice = "";
		}

	} while (!nerr);
	std::cout << "Loading GUI..." << std::endl;
	editor.run();

}

/**
* Launch the game
*/
void Bootstrap::launch_game()
{
	LOG(DEBUG) << "Launching Game";
	std::cout << "Launching dat game..." << std::endl;
	// TODO Game class ( game.run() )
	Game game(this);
	game.run();
	//test_sfml();
}
