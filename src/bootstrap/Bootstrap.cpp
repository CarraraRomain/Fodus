#include "Bootstrap.hpp"



Bootstrap::Bootstrap()
{
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
	loadConf();
	//loadFile("tiles");
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