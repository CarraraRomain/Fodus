#include "Game.hpp"
#include "../render/Animation.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../engine/MoveCommand.h"


Game::Game(Bootstrap* boot, Engine* eng) : Observer(&eng->getState()),
m_boot(boot), m_game_engine(eng), m_isKeyPressed(false)
{
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
}

/**
 * Global load method
 */
void Game::load()
{
	load_gui();
	//m_game_engine.reset(new Engine);
	
}

/**
 * Main entry point
 */
void Game::run()
{
	LOG(DEBUG) << "Game is running";
	
	ElementList list;
	
	load();
	LOG(DEBUG) << "Updating";
	
	
	update();
	
	LOG(DEBUG) << "Loop";
	while(m_game_window->isOpen())
	{
		game_event_loop();
		handle_keys();

//		sf::Time frameTime = frameClock.restart();

		m_game_window->clear();
		m_game_window->draw(*m_game_scene);

		m_game_window->display();
	}
	LOG(DEBUG) << "Game ended";
}

void Game::update()
{
	m_game_scene->update(*(static_cast<Etat*>(m_sub)->getList()));
}

/**
 * Handle keyboard commands
 */
void Game::handle_keys()
{
	bool move = false;
	int x(0), y(0), uid(42);
	AnimationType type = MoveForward;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		move = true;
		x = 0;
		y = -1;
		type = MoveForward;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		move = true;
		x = 0;
		y = 1;
		type = MoveBackward;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		move = true;
		x = -1;
		y = 0;
		type = MoveLeft;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		move = true;
		x = 1;
		y = 0;
		type = MoveRight;
	}

	if (move && !m_isKeyPressed)
	{
		MoveCommand command = MoveCommand(m_game_engine, x, y, type, uid);
		command.execute();
		m_isKeyPressed = true;
		// Call an updaye right after the command execution
		// TODO the update should be called by the obs pattern instead
		//m_game_scene->update(*m_game_engine->getState().getList());
	}
	

}

void Game::game_event_loop()
{
	sf::Event Event;
	while (m_game_window->pollEvent(Event)) {
		if (Event.type == sf::Event::Closed)
			m_game_window->close();
		if(Event.type == sf::Event::KeyReleased)
		{
			m_isKeyPressed = false;
		}
	}
	

	

}

