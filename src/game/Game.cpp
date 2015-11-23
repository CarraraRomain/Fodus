#include "Game.hpp"
#include "../render/Animation.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../engine/MoveCommand.h"
#include "../engine/EndTurnCommand.hpp"
#include "../engine/AttackCommand.h"


Game::Game(Bootstrap* boot, Engine* eng) : Observer(&eng->getState()),
m_boot(boot), m_game_engine(eng), m_hud(boot), m_isKeyPressed(false)
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
	
	m_filter.setPosition(OFFSET_X*SIZE, OFFSET_Y*SIZE);
	m_filter.setSize(sf::Vector2f(WIDTH*SIZE, HEIGHT *SIZE));
	m_filter.setFillColor(sf::Color(0,0,0,142));
	
}

/**
 * Global load method
 */
void Game::load()
{
	load_gui();
	m_hud.load(m_game_window->getSize());
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
		m_game_engine->run();
		//handle_event();
		m_game_scene->updateAnims();
		if (!m_game_scene->isAnimationRunning() && is_playing ) {
			enableActions();
		}
		
//		sf::Time frameTime = frameClock.restart();

		m_game_window->clear();
		m_game_window->draw(m_hud);
		//m_game_window->draw(m_dashboard);
		m_game_window->draw(*m_game_scene);
		if (m_disable_actions) m_game_window->draw(m_filter);
		//test_hud();
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
			m_hud.updateTurns(m_turns);
			is_playing = true;
			for (auto it : m_move_watcher) m_move_watcher[it.first] = false;
		}
		watchMovements();
		m_game_scene->update(*(static_cast<Etat*>(m_sub)->getList()));

		break;
	}
	updateHUD();
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
		try {
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
				if (m_disable_actions) throw std::logic_error("Action disabled");
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
							disableActions();
						}
					}
					else LOG(DEBUG) << "You have already played!";
					if (x >= 11 * SIZE			&& x < 19 * SIZE		&&
						y >= SIZE*(6 + HEIGHT) && y < SIZE*(8 + HEIGHT))
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
				if (m_disable_actions) throw std::logic_error("Action disabled");
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
					AttackCommand commandA = AttackCommand(m_game_engine, 1, 89, 1);
					commandA.execute();
				}

				if (move && !m_isKeyPressed)
				{
					MoveCommand command = MoveCommand(m_game_engine, x, y, type, uid, m_player_id);
					command.execute();
					disableActions();
					m_isKeyPressed = true;

				}
			}
			// End Keyboard
		}catch(std::logic_error e)
		{
			LOG(DEBUG) << e.what();
		}
	}
}


void Game::updateHUD()
{
	
	if (m_has_played || m_game_engine->getPlayer(m_player_id).hasMoved(1)) {
		m_hud.updateMoveCapa(false);
	}
	else
	{
		m_hud.updateMoveCapa(true);
	} 
	if (m_has_played || m_game_engine->getPlayer(m_player_id).hasAttacked(1)) {
		m_hud.updateAttackCapa(false);
	}
	else
	{
		m_hud.updateAttackCapa(true);
	}

}

void Game::endPlayerTurn()
{
	disableActions();
	is_playing = false;
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
					disableActions();
				}
				
			}
		}

	}

}

void Game::disableActions()
{
	m_disable_actions = true;
	m_hud.actionsDisabled();
}

void Game::enableActions()
{
	m_disable_actions = false;
	m_hud.actionsEnabled();
	
}