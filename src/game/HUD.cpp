#include "HUD.hpp"

using namespace game;

HUD::HUD(boot::Bootstrap* boot): m_boot(boot)
{

}


HUD::~HUD()
{
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_dashboard, states);

	for(auto txt: m_text_map)
	{
		target.draw(txt.second, states);
	}
}

void HUD::load(sf::Vector2u window_size)
{
	
	m_window_size = window_size;

	if (!m_font.loadFromFile(m_boot->getPath("font"))) LOG(FATAL) << "Font not found";
	if (!m_dashboard_texture.loadFromFile(m_boot->getPath("dashboard"),
		sf::IntRect(0, 0, window_size.x, window_size.y))) LOG(FATAL) << "HUD not found";
	m_dashboard.setSize(sf::Vector2f(window_size));
	m_dashboard.setTexture(&m_dashboard_texture);

	m_text_map["turn"] = sf::Text();
	setFont("turn");
	m_text_map["turn"].setColor(sf::Color::White);
	m_text_map["turn"].setCharacterSize(42);
	m_text_map["turn"].setString("Tour: 0");

	sf::FloatRect bbox = m_text_map["turn"].getGlobalBounds();
	m_text_map["turn"].setOrigin(bbox.width / 2, bbox.height / 2);
	m_text_map["turn"].setPosition(window_size.x / 2, window_size.y - 48);


	// FODUS
	m_text_map["fodus"] = sf::Text();
	setFont("fodus");
	m_text_map["fodus"].setColor(sf::Color::White);
	m_text_map["fodus"].setCharacterSize(24);
	m_text_map["fodus"].setString("Fodus 2.F");

	bbox = m_text_map["fodus"].getGlobalBounds();
	m_text_map["fodus"].setOrigin(bbox.width / 2, bbox.height / 2);
	m_text_map["fodus"].setPosition(window_size.x/ 2, 16);

	// Commands
	m_text_map["command"] = sf::Text();
	setFont("command");
	m_text_map["command"].setColor(sf::Color::White);
	m_text_map["command"].setCharacterSize(24);
	m_text_map["command"].setString("Echap: Next Turn | A: Fireball | Z: Spawn | Q+Mouse: Move");

	bbox = m_text_map["command"].getGlobalBounds();
	m_text_map["command"].setOrigin(bbox.width / 2, bbox.height / 2);
	m_text_map["command"].setPosition(window_size.x / 2, window_size.y - 128);
	
	// Attack
	m_text_map["attack"] = sf::Text();
	setFont("attack");
	m_text_map["attack"].setColor(sf::Color::White);
	m_text_map["attack"].setCharacterSize(24);
	m_text_map["attack"].setString("Attack possible");

	//bbox = m_text_map["attack"].getGlobalBounds();
	//m_text_map["attack"].setOrigin(0, 0);
	m_text_map["attack"].setPosition(16, window_size.y-32);
	LOG(DEBUG) << "Origin : " << m_text_map["attack"].getOrigin().y;
	// Move
	m_text_map["move"] = sf::Text();
	setFont("move");
	m_text_map["move"].setColor(sf::Color::White);
	m_text_map["move"].setCharacterSize(24);
	m_text_map["move"].setString("Move possible");

	bbox = m_text_map["move"].getGlobalBounds();
	m_text_map["move"].setOrigin(bbox.width,0);
	m_text_map["move"].setPosition(window_size.x - 16, window_size.y - 32);

	// Action
	m_text_map["action"] = sf::Text();
	setFont("action");
	m_text_map["action"].setColor(sf::Color::White);
	m_text_map["action"].setCharacterSize(24);
	m_text_map["action"].setString("Selected Action:");

	bbox = m_text_map["action"].getGlobalBounds();
	m_text_map["action"].setOrigin(bbox.width, 0);
	m_text_map["action"].setPosition(window_size.x - 16,8);
	// Action Name
	m_text_map["action_name"] = sf::Text();
	setFont("action_name");
	m_text_map["action_name"].setColor(sf::Color::White);
	m_text_map["action_name"].setCharacterSize(24);
	m_text_map["action_name"].setString("None");

	bbox = m_text_map["action_name"].getGlobalBounds();
	m_text_map["action_name"].setOrigin(bbox.width, 0);
	m_text_map["action_name"].setPosition(window_size.x - 32,32);



}

void HUD::updateTurns(const int turns)
{
	m_turns = turns;
	m_text_map["turn"].setString("Tour: " + std::to_string(m_turns));
	m_text_map["turn"].setColor(sf::Color::White);
}

void HUD::updateMoveCapa(bool b)
{
	if (b)
	{
		m_text_map["move"].setString("Move possible");
		m_text_map["move"].setColor(sf::Color::Green);

	}
	else
	{
		m_text_map["move"].setString("No more move");
		m_text_map["move"].setColor(sf::Color::Red);
	}
	sf::FloatRect bbox = m_text_map["move"].getGlobalBounds();
	m_text_map["move"].setOrigin(bbox.width, 0);
}

void HUD::updateAttackCapa(bool b)
{
	if (b)
	{
		m_text_map["attack"].setString("Action possible");
		m_text_map["attack"].setColor(sf::Color::Green);

	}
	else
	{
		m_text_map["attack"].setString("No more action");
		m_text_map["attack"].setColor(sf::Color::Red);
	}
}

void HUD::turnFinished()
{
	m_disable_action = true;
}

void HUD::newTurn()
{
	m_disable_action = false;
}

void HUD::actionsDisabled()
{
	m_text_map["turn"].setString("Playing...");
	m_text_map["turn"].setColor(sf::Color::Red);
}

void HUD::actionsEnabled()
{
	updateTurns(m_turns);
}

void HUD::updateAction(int skillMode)
{
	std::string action;
	switch (skillMode)
	{
	case 1:
		action = "Attack";
		break;
	case 2:
		action = "Fireball";
		break;
	case 3:
		action = "Spawn";
		break;
	default:
		action = "None";
	}

	m_text_map["action_name"].setString(action);
}

void HUD::setFont(std::string key)
{
	m_text_map[key].setFont(m_font);
}
