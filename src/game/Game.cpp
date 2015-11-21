#include "Game.hpp"
#include "../render/Animation.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../engine/MoveCommand.h"
#include "../engine/EndTurnCommand.hpp"
#include "../engine/AttackCommand.h"


Game::Game(Bootstrap* boot, Engine* eng) : Observer(&eng->getState()),
m_boot(boot), m_game_engine(eng), m_isKeyPressed(false)
{
	m_client_id = rand();
	m_player_id = 1;
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
	int width = (2*OFFSET_X + WIDTH)*SIZE;
	int height = (OFFSET_Y + HEIGHT + OFFSET_BOT)*SIZE;
	LOG(DEBUG) << "Loading GUI";
	m_game_scene.reset(new Scene(m_boot));
	m_game_window.reset(new sf::RenderWindow(sf::VideoMode(width, height),
		"Fodus", sf::Style::Titlebar | sf::Style::Close));
	
	if (!m_font.loadFromFile(m_boot->getPath("font"))) LOG(FATAL) << "Font not found";
	if (!m_dashboard_texture.loadFromFile(m_boot->getPath("dashboard"),
		sf::IntRect(0, 0, 960, 768))) LOG(FATAL) << "HUD not found";
	t_turns.setFont(m_font);
	t_turns.setColor(sf::Color::White);
	t_turns.setCharacterSize(42);
	m_dashboard.setSize(sf::Vector2f(960, 768));
	m_dashboard.setTexture(&m_dashboard_texture);
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
		m_player_id = m_game_engine->getCurrentPlayer();

		if (m_game_engine->getPlayer(m_player_id).isHuman())
			game_event_loop();
		else {
			Ai::execute(m_player_id,m_game_engine);
		}
		//handle_event();
		m_game_scene->updateAnims();
//		sf::Time frameTime = frameClock.restart();

		m_game_window->clear();
		m_game_window->draw(m_dashboard);
		m_game_window->draw(*m_game_scene);
		test_hud();
		m_game_window->display();
	}
	LOG(DEBUG) << "Game ended";
}

void Game::update(ObsType type)
{
	m_has_played = m_game_engine->hasPlayed(m_player_id);
	switch (type)
	{
	case ObsEngine:
		
		break;
	case ObsState:
		if(static_cast<Etat*>(m_sub)->getTurn() != m_turns)
		{
			LOG(DEBUG) << "New Turn!";
			m_turns = static_cast<Etat*>(m_sub)->getTurn();
			for (auto it : m_move_watcher) m_move_watcher[it.first] = false;
		}
		watchMovements();
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
	int x(0), y(0), uid(1);
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
				int x = event.mouseButton.x;
				int y = event.mouseButton.y;
				// if has already played, disabled
				if (!m_has_played) {
					// Game area : X OFFSET_X to WIDTH /SIZE
					//             Y OFFSET_Y to HEIGHT
					
					if (x >= OFFSET_X * SIZE && x < (OFFSET_X + WIDTH)*SIZE &&
						y >= OFFSET_Y * SIZE && y < (OFFSET_Y + HEIGHT)*SIZE)
					{
						// This is the game area
						move = true;
						x -= OFFSET_X * SIZE;
						y -= OFFSET_Y * SIZE;
						LOG(DEBUG) << "X: " << int(x / SIZE);
						LOG(DEBUG) << "Y: " << int(y / SIZE);
						MoveCommand command = MoveCommand(m_game_engine, (x / SIZE), y / SIZE, MoveRight, 1, m_player_id);
						command.execute();
					}
				}
				else LOG(DEBUG) << "You have already played!";
				if(x >= 11*SIZE			&& x <19*SIZE		&& 
						y >= SIZE*(6+HEIGHT)	&& y < SIZE*(8+HEIGHT))
				{
					// Next turn button 
					endPlayerTurn();
				}
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
			if (event.key.code == sf::Keyboard::Escape)
			{
				// End Turn
				endPlayerTurn();
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				AttackCommand commandA = AttackCommand(m_game_engine,1, 89);
				commandA.execute();
			}

			if (move && !m_isKeyPressed)
			{
				MoveCommand command = MoveCommand(m_game_engine, x, y, type, uid, m_player_id);
				command.execute();
				m_isKeyPressed = true;

			}
		}
		// End Keyboard
	}
}


void Game::test_hud()
{
	sf::Vector2u vect = m_game_window->getSize();
	int width(vect.x), height(vect.y);

	sf::Text text, move, attack, command;
	sf::String m_string, a_string;
	// select the font
	text.setFont(m_font); // font is a sf::Font
	move.setFont(m_font); // font is a sf::Font
	attack.setFont(m_font); // font is a sf::Font
	command.setFont(m_font); // font is a sf::Font

						// set the string to display
	text.setString("FODUS 2.2");
	command.setString("Echap (twice): Next Turn | Space: Attack | Mouse: Move");
	if (m_has_played || m_game_engine->getPlayer(m_player_id).hasMoved(1)) {
		move.setString("Move done");
		move.setColor(sf::Color::Red);
	}
	else
	{
		move.setString("Move possible");
		move.setColor(sf::Color::Green);
	} 
	if (m_has_played || m_game_engine->getPlayer(m_player_id).hasAttacked(1)) {
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
	command.setCharacterSize(30); // in pixels, not points!

							   // set the color
	text.setColor(sf::Color::White);
	command.setColor(sf::Color::White);

	sf::FloatRect bbox = text.getGlobalBounds();
	text.setOrigin(bbox.width / 2, bbox.height / 2);
	text.setPosition(width / 2, 16);

	// Attack left corner bot
	bbox = attack.getGlobalBounds();
	attack.setOrigin(0, bbox.height+20);
	attack.setPosition(20, height);
	// Move right corner bot
	bbox = move.getGlobalBounds();
	move.setOrigin(bbox.width, 20+bbox.height);
	move.setPosition(width- 20, height);
	// Turns
	bbox = text.getGlobalBounds();
	t_turns.setOrigin(bbox.width / 2, bbox.height / 2);
	t_turns.setPosition(width / 2, height - 64);
	// Commands
	bbox = command.getGlobalBounds();
	command.setOrigin(bbox.width / 2, bbox.height / 2);
	command.setPosition(width / 2, height - 128);

	m_game_window->draw(text);
	m_game_window->draw(move);
	m_game_window->draw(attack);
	m_game_window->draw(command);
	t_turns.setString("Tour: " + std::to_string(m_turns));
	m_game_window->draw(t_turns);
}

void Game::endPlayerTurn()
{
	EndTurnCommand command = EndTurnCommand(m_game_engine, m_player_id);
	command.execute();
}

void Game::watchMovements()
{
	// Check moves for each player
	for(auto pl: m_game_engine->getPlayers())
	{
		// check move for each unit
		for (std::map<int, bool>::iterator it = pl.second.getMovedBegin(); 
				it != pl.second.getMovedEnd();++it)
		{
			if(pl.second.hasMoved(it->first))
			{
				// Player has moved, request an animation
				LOG(DEBUG) << "Move asked";
				if(!m_move_watcher[pl.second.getId()] )
				{
					m_game_scene->addPendingMovement(pl.second.getId(), pl.second.getMove(pl.second.getId()));
					m_move_watcher[pl.second.getId()] = true;
				}
				
			}
		}

	}

}