#include "Game.hpp"
#include "../render/Animation.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../engine/MoveCommand.h"
#include "../engine/EndTurnCommand.hpp"


Game::Game(Bootstrap* boot, Engine* eng) : Observer(&eng->getState()),
m_boot(boot), m_game_engine(eng), m_isKeyPressed(false)
{
	m_client_id = rand();
	m_player_id = 42;
	LOG(DEBUG) << "Client ID: " << m_client_id;
}


Game::~Game()
{
}

/**
 * Load the Game GUI
 */
void Game::load_gui()
{
	LOG(DEBUG) << "Loading GUI";
	m_game_scene.reset(new Scene(m_boot));
	m_game_window.reset(new sf::RenderWindow(sf::VideoMode(SIZE*WIDTH,
		SIZE*HEIGHT), "Level", sf::Style::Titlebar | sf::Style::Close));
	m_hud_window.reset(new sf::RenderWindow(sf::VideoMode(SIZE*WIDTH,
		200), "HUD", sf::Style::Titlebar ));
	m_hud_window->setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width  - SIZE*WIDTH) / 2, 0));
	if (!m_font.loadFromFile(m_boot->getPath("font"))) LOG(FATAL) << "Font not found";
	t_turns.setFont(m_font);
	t_turns.setColor(sf::Color::White);
	t_turns.setCharacterSize(42);
}

/**
 * Global load method
 */
void Game::load()
{
	load_gui();
	//m_game_engine.reset(new Engine);
	int rc = m_game_engine->connect(m_client_id);
	if(rc>= 400) LOG(FATAL) << "Cannot connect to engine: " << rc;
	rc = m_game_engine->registerPlayer(m_client_id, m_player_id);
	if (rc >= 400) LOG(FATAL) << "Cannot register player in engine: " << rc;
	LOG(DEBUG) << "Connected to local, CID: " << m_client_id << ", PID: " << m_player_id;
}

/**
 * Main entry point
 */
void Game::run()
{
	LOG(DEBUG) << "Game is running";
	
	
	load();
	// Force update
	update(ObsState);
	
	LOG(DEBUG) << "Loop";
	while(m_game_window->isOpen())
	{
		game_event_loop();
		hud_event_loop();
		//handle_event();

//		sf::Time frameTime = frameClock.restart();

		m_game_window->clear();
		m_hud_window->clear();
		m_game_window->draw(*m_game_scene);
		test_hud();
		m_game_window->display();
		m_hud_window->display();
	}
	LOG(DEBUG) << "Game ended";
}

void Game::update(ObsType type)
{
	switch (type)
	{
	case ObsEngine:
		break;
	case ObsState:
		m_turns = static_cast<Etat*>(m_sub)->getTurn();
		m_game_scene->update(*(static_cast<Etat*>(m_sub)->getList()));
		break;
	}
	
}

/**
 * Event loop (shall be unique)
 */
void Game::game_event_loop()
{
	sf::Event event;
	int x(0), y(0), uid(42);
	bool move = false;

	while (m_game_window->pollEvent(event)) {
		// Global events
		if (event.type == sf::Event::Closed)
			m_game_window->close();
		if(event.type == sf::Event::KeyReleased)
		{
			m_isKeyPressed = false;
		}
		// End global
		
		// Mouse events
		if (event.type == sf::Event::MouseButtonPressed)
		{
		
			if (event.mouseButton.button == (sf::Mouse::Left))
			{
				move = true;
				LOG(DEBUG) << "X: " << int(event.mouseButton.x / SIZE);
				MoveCommand command = MoveCommand(m_game_engine, (event.mouseButton.x / SIZE), event.mouseButton.y / SIZE, MoveRight, 42);
				command.execute();
			}
		}
		// End mouse

		// Keyboard events
		if (event.type == sf::Event::KeyPressed)
		{
			AnimationType type = MoveForward;
			if (event.key.code == sf::Keyboard::Up)
			{
				move = true;
				x = 100;
				y = 99;
				type = MoveForward;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				move = true;
				x = 100;
				y = 101;
				type = MoveBackward;
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				move = true;
				x = 99;
				y = 100;
				type = MoveLeft;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				move = true;
				x = 101;
				y = 100;
				type = MoveRight;
			}

			if (move && !m_isKeyPressed)
			{
				MoveCommand command = MoveCommand(m_game_engine, x, y, type, uid);
				command.execute();
				m_isKeyPressed = true;

			}
		}
		// End Keyboard
	}
}

void Game::hud_event_loop()
{
	sf::Event event;
	int x(0), y(0), uid(42);
	bool move = false;

	while (m_hud_window->pollEvent(event)) {
		// Global events
		if (event.type == sf::Event::Closed)
			m_game_window->close();
		if (event.type == sf::Event::KeyReleased)
		{
			m_isKeyPressed = false;
		}
		// End global

		// Mouse events
		if (event.type == sf::Event::MouseButtonPressed)
		{

			if (event.mouseButton.button == (sf::Mouse::Left))
			{
				move = true;
				//LOG(DEBUG) << "X: " << (int)(event.mouseButton.x / SIZE);
				EndTurnCommand command = EndTurnCommand(m_game_engine, 42);
				command.execute();
			}
		}
		// End mouse

	}
}

void Game::test_hud()
{
	sf::Vector2u vect = m_hud_window->getSize();
	int width(vect.x), height(vect.y);

	sf::Text text, move, attack;
	sf::String m_string, a_string;
	// select the font
	text.setFont(m_font); // font is a sf::Font
	move.setFont(m_font); // font is a sf::Font
	attack.setFont(m_font); // font is a sf::Font

						// set the string to display
	text.setString("FODUS 2.2");
	if (m_game_engine->getPlayer(m_player_id).hasMoved()) {
		move.setString("Move done");
		move.setColor(sf::Color::Red);
	}
	else
	{
		move.setString("Move possible");
		move.setColor(sf::Color::Green);
	} 
	if (m_game_engine->getPlayer(m_player_id).hasAttacked()) {
		attack.setString("Attack done");
		attack.setColor(sf::Color::Red);
	}
	else
	{
		attack.setString("Attack possible");
		attack.setColor(sf::Color::Green);
	} 
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	attack.setCharacterSize(24); // in pixels, not points!
	move.setCharacterSize(24); // in pixels, not points!

							   // set the color
	text.setColor(sf::Color::White);
	sf::FloatRect bbox = text.getGlobalBounds();
	text.setOrigin(bbox.width / 2, bbox.height / 2);
	text.setPosition(width / 2, height/2);

	// Attack left corner bot
	bbox = attack.getGlobalBounds();
	attack.setOrigin(0, bbox.height+20);
	attack.setPosition(20, height);
	// Move right corner bot
	bbox = move.getGlobalBounds();
	move.setOrigin(bbox.width, 20+bbox.height);
	move.setPosition(width- 20, height);

	m_hud_window->draw(text);
	m_hud_window->draw(move);
	m_hud_window->draw(attack);
	t_turns.setString("Tour: " + std::to_string(m_turns));
	m_hud_window->draw(t_turns);
}
