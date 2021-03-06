#include "Bootstrap.hpp"

#include "../editor/Editor.hpp"
#include "../game/Game.hpp"
#include "../ai/AiPlayer.hpp"
#include "../engine/Engine.hpp"

#include "../network/NetworkClient.hpp"
#include "../network/NetworkEngine.hpp"

using namespace boot;

/**
 * Handle signals in order to kill child process
 */
void Bootstrap::signalHandler(const boost::system::error_code& error, int signal_number)
{
	std::string str;
	LOG(WARNING) << "Signal Handler";
	if (!error){
		if(signal_number == SIGTERM) str = "SIGTERM";
		if(signal_number == SIGSEGV) str = "SIGSEGV";
		if(signal_number == SIGINT) str = "SIGINT";

		if(m_pid_router > 0) kill(m_pid_router, SIGTERM);
		if(str != ""){
			std::cout<<"Recvd " << str << ", exiting ..";
			exit(0);
		}

		return;
	}
	std::cerr<<"signalHandler() :"<<error.message();
	return;
}


void Bootstrap::handleCommand(engine::Command* com)
{
	LOG(DEBUG) << "Command received by Bootstrap";
	switch(com->type)
	{
	case Mode:
		LOG(DEBUG) << "Executing Mode Command";
		std::string mode = dynamic_cast<engine::ModeCommand*>(com)->mode;
		LOG(DEBUG) << "Will launch " << mode << " mode";
		if (mode == "editor") launch_editor();
		else if (mode == "game") launch_game();
		break;
	}
}

Bootstrap::Bootstrap(int argc, char** argv)
		: signals(io, SIGTERM, SIGINT, SIGSEGV)
{
	m_pid_router = 0;
	m_argc = argc;
	m_argv = argv;
}
Bootstrap::Bootstrap()
		: signals(io, SIGTERM, SIGINT, SIGSEGV)
{
	m_pid_router = 0;
	m_argc = 0;
	m_argv = nullptr;
}


Bootstrap::~Bootstrap()
{
}

/**
 * Load the global conf
 * FATAL failure if it fails
 */
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


/**
 * Load the level index
 */
void Bootstrap::loadLevelIndex() {
loadFile("levels_index");
}

/**
 * Init method
 */
void Bootstrap::start()
{
	LOG(DEBUG) << "Bootstrap is starting";

	signals.async_wait(
			boost::bind(&Bootstrap::signalHandler,
						this, boost::asio::placeholders::error,
						boost::asio::placeholders::signal_number));
	boost::thread th(boost::bind(&boost::asio::io_service::run, &io));
	loadConf();
	loadLevelIndex();
	
}

void Bootstrap::listLevels()
{
 
 rapidjson::Document& index = 	*m_docs["levels_index"];
 rapidjson::Value::ConstMemberIterator it;
 for (it = index["levels"].MemberBegin(); it != index["levels"].MemberEnd();++it)
 {
	 std::cout << "| "<< it->name.GetString() << " : " << it->value["desc"].GetString() << std::endl;
 }
}

std::string Bootstrap::chooseLevel()
{
	std::string level;
	std::cout << "Choose a level to play:" << std::endl;
	do {
		listLevels();
		std::cout << "Your choice: ";
		std::cin >> level;
	} while (!checkLevelNode(level));
	return level;
}

/**
 * Main method
 */
void Bootstrap::run()
{
	
	LOG(DEBUG) << "Bootstrap is running";
	// Launch Args
	// TODO to complete
	std::string type;
	engine::ModeCommand command = engine::ModeCommand(this, type);
	if (m_argc > 1) type = m_argv[1];
	
	if (type == "editor" || type == "game") command.mode = type;
	else {
		do
		{
			std::cout << "> Launch game or level editor? (game/editor) ";
			std::cin >> type;
			if (type == "editor" || type == "game") command.mode = type;
		} while (type != "game" && type != "editor");
	}
	command.execute();
	LOG(DEBUG) << "Bootstrap ended";
}
/**
 * TODO Implementation
 */
void Bootstrap::getConfig(const std::string&) const
{
}

/**
 * Get a doc ; if not already loaded loads it from the disk
 */
std::shared_ptr<rapidjson::Document> Bootstrap::getDocument(const std::string& key)
{
	std::map < std::string, std::shared_ptr<rapidjson::Document>>::const_iterator it;
	rapidjson::Document re;

	it = m_docs.find(key);
	if (it != m_docs.end()) return it->second;
	
	
	loadFile(key);

	return getDocument(key);
	
}

/**
 * Load and parses a level from disk
 */
std::shared_ptr<rapidjson::Document> Bootstrap::getLevel(const std::string& name) {

	LOG(DEBUG) << "Opening level " << name;
	std::shared_ptr<rapidjson::Document> file;
	file.reset(new rapidjson::Document());
	file->SetObject();
	if(!checkLevelNode(name))
	{
		LOG(ERROR) << "Cannot load level " << name;
		throw std::invalid_argument("No such res");
	}
	// TODO check levels_path
	std::string path = m_config["resources"]["levels_path"].GetString();
	std::stringstream ss;
	std::ifstream ifs;
	ifs.open(path + name + ".json", std::ios::binary);
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
		LOG(ERROR) << "Level file not found";
		throw std::invalid_argument("Level file not found");
	}
	ifs.close();

	LOG(DEBUG) << "Loaded level " << name;
	return file;
}
/**
 * Get a resource path
 */
std::string Bootstrap::getPath(const std::string& name) {

	LOG(DEBUG) << "Opening res " << name;
	if(!checkNode(name))
	{
		LOG(ERROR) << "Cannot load res " << name;
		throw std::invalid_argument("No such res");
	}
	std::string path = m_config["resources"][name].GetString();
	LOG(DEBUG) << "Loaded res " << name;
	return path;

}

/**
 * Load and parse a JSON file from disk
 */
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

/**
 * TODO Implementation
 */
void Bootstrap::loadLevel(const std::string &name) {

}

bool Bootstrap::checkNode(const std::string& name) const
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
 * TODO Implementation
 */
bool Bootstrap::checkLevelNode(const std::string& name)
{
	rapidjson::Document& index = *m_docs["levels_index"];
	if (!index["levels"].HasMember(name)) {
		LOG(ERROR) << "No such level " << name;
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
	editor.run();
}

/**
 * Launch the game
 */
void Bootstrap::launch_game()
{
	LOG(DEBUG) << "Launching Game";

	LOG(INFO) << "Main thread : " << std::this_thread::get_id();

	std::string mode;
	do
	{
		std::cout <<"> Local mode or network? (l/n) ";
		std::cin >> mode;
	}while(mode != "l" && mode != "n");

	if(mode == "l")
	{
		std::string level = chooseLevel();
		engine::Engine engine(this);
		game::Game game(this, &engine, rand());
		ai::AiPlayer aiP(this, &engine, rand());

		engine.loadLevel(level);
		game.start();
		aiP.start();
		engine.start();

		std::thread th(std::ref(engine));
		//th.detach();
		//  if(th.joignable())
		std::thread aith(std::ref(aiP));

		game.run();

		//aiP.run();
		th.join();
		aith.join();
		//launch_game();
	}
	else if (mode == "n")
	{
		std::string choice;
		do
		{
			std::cout <<"> Launch Router? (y/n) ";
			std::cin >> choice;
		}while(choice != "y" && choice != "n");
		if(choice == "y")
		{
			choice = "";
			m_pid_router = fork();
			if( m_pid_router == 0)
			{
				LOG(DEBUG) << "Bonefish launch";
				int rc= execlp("/bin/bash", "/bin/sh", "-c",  "./router -r \"fodus\" -t 9999", NULL);
				LOG(DEBUG) << rc;
				if(rc<0) exit(-1);
			}
			LOG(DEBUG) << "Routeur launched";
		}

		launch_network();

	}

}

void Bootstrap::launch_network()
{
	LOG(DEBUG) << "Launch with network";
	network::NetworkEngine engine(this);

	network::NetworkClient game(this, &engine, rand());
	ai::AiPlayer aiP(this, &engine, rand());
	engine.loadLevel("test");
	engine.start();
	game.start();
	aiP.start();

	LOG(DEBUG) << "Running on network";
	std::thread th(std::ref(engine));
	//th.detach();
	//  if(th.joignable())
	std::thread aith(std::ref(aiP));

//	sleep(6);
	game.run();
	LOG(DEBUG) << "Joining threads";
	//aiP.run();
	th.join();
	aith.join();

	//launch_game();
	LOG(DEBUG) << "Exiting";
	exit(0);
}
