#include "Game.hpp"
#include "../render/Animation.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../engine/MoveCommand.h"
#include "../engine/EndTurnCommand.hpp"
#include "../engine/AttackCommand.h"


/*
Game::Game(Bootstrap* boot, Engine* eng) : Observer(&eng->getState()),
m_boot(boot), getEngine()(eng), m_hud(boot), m_isKeyPressed(false)
{
	m_client_id = rand();
	m_player_id = 1;
	LOG(DEBUG) << "Client ID: " << m_client_id;
}
*/


Game::Game(Bootstrap* boot, AbstractEngine* engine, int cid): IGame(boot, engine, cid), m_hud(boot), m_game_scene(boot)
{
	m_has_played = false;
	
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
	int width = (2*OFFSET_X + WIDTH)*SIZE;
	int height = (OFFSET_Y + HEIGHT + OFFSET_BOT)*SIZE;
	m_game_window.reset(new sf::RenderWindow(sf::VideoMode(width, height),
		"Fodus", sf::Style::Titlebar | sf::Style::Close));
}

/**
 * Global load method
 */
void Game::load()
{
	load_gui();
	m_hud.load(m_game_window->getSize());

}

/**
 * Main entry point
 */
void Game::run()
{
	LOG(DEBUG) << "Game is running";
	
	skillMode = 0;
	
	load();
	// Force update
	//update(ObsState);
	// Request a full update
	syncRequest();
	//m_game_scene.notify();
	update(ObsState);
	m_player_playing = 1;
	LOG(DEBUG) << "Loop";
	while(m_game_window->isOpen())
	{


		if (m_player_playing == 1) game_event_loop();
		
		getEngine()->run();
		//handle_event();
		m_game_scene.updateAnims();
		if (!m_game_scene.isAnimationRunning() && is_playing ) {
			enableActions();
		}
		
//		sf::Time frameTime = frameClock.restart();

		m_game_window->clear();
		m_game_window->draw(m_hud);
		
		m_game_window->draw(m_game_scene);
		//if (m_disable_actions) m_game_window->draw(m_filter);
		m_game_window->display();
	}
	LOG(DEBUG) << "Game ended";
}

void Game::start()
{
	// This Client has Player 1 (Human) and player 2 (IA)
	m_players_id.push_back(1);
	//m_players_id.push_back(2);	
	//m_players_id.push_back(3);

	// register to the engine to receive update
	for (int pl : m_players_id)
	{
		int rc = getEngine()->connect(pl);
		if (rc >= 400) LOG(FATAL) << "Cannot connect to engine: " << rc;
		rc = getEngine()->registerPlayer(pl, this);
		if (rc >= 400) LOG(FATAL) << "Cannot register to engine: " << rc;

	}


	LOG(DEBUG) << "Connected to local, CID: " << m_client_id << ", PID: " << m_players_id[0];

}

void Game::update(ObsType type)
{
	LOG(WARNING) << "DEPRECATED UPDATE";
	//m_has_played = getEngine()->hasPlayed(m_player_id);
	switch (type)
	{
	case ObsEngine:
		
		break;
	case ObsState:
		Etat state = getEngine()->getState();
		if(state.getTurn() != m_turns)
		{
			LOG(DEBUG) << "New Turn!";
			m_turns = state.getTurn();
			m_hud.updateTurns(m_turns);
			is_playing = true;
			for (auto it : m_move_watcher) m_move_watcher[it.first] = false;
		}
		watchMovements();
		std::vector<std::vector<int>> map = getEngine()->getMap(1);
		if(is_playing) m_game_scene.getInfos()->syncMoveMap(map);
		else m_game_scene.getInfos()->resetMoveMap();
		m_game_scene.update(m_list);

		break;
	}
	updateHUD();
}

void Game::updateGlobal(Etat& e)
{
	LOG(INFO) << "UPDATE : GLOBAL";
	if (e.getTurn() != m_turns)
	{
		LOG(DEBUG) << "New Turn!";
		m_turns = e.getTurn();
		m_hud.updateTurns(m_turns);
		is_playing = true;
		for (auto it : m_move_watcher) m_move_watcher[it.first] = false;
	}
	watchMovements();
	std::vector<std::vector<int>> map = getEngine()->getMap(1);
	if (is_playing) m_game_scene.getInfos()->syncMoveMap(map);
	else m_game_scene.getInfos()->resetMoveMap();
	m_game_scene.update(*e.getList());
	updateHUD();
}

void Game::updateElement(Element& el)
{
}

void Game::updateTurn(int turn)
{
}

void Game::updateNowPlaying(int pid)
{
	m_player_playing = pid;
	if (m_players_id[0] == pid) is_playing = true;
}

void Game::canPlay(int pid)
{
}

void Game::hasPlayed(int pid)
{
}

void Game::sync(ElementList list)
{
}

void Game::syncRequest()
{
	m_list = getEngine()->syncRequest();
}

void Game::whoIsPlaying()
{
	m_player_playing = getEngine()->whoIsPlaying();
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

							if (skillMode == 0) {
								MoveCommand command = MoveCommand(getEngine(), (x / SIZE), y / SIZE, MoveRight, 1, m_player_playing);
							command.execute();
							}
							else if(skillMode == 1){
								SkillCommand command = SkillCommand(getEngine(), (x / SIZE), y / SIZE, 1, 0, m_player_playing);
								command.execute();
								skillMode = 0;
							}

							
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
					AttackCommand commandA = AttackCommand(getEngine(), 1, 89, 1);
					commandA.execute();
				}
				if (event.key.code == sf::Keyboard::A)
				{
					skillMode = 1;
				}

				if (move && !m_isKeyPressed)
				{
					MoveCommand command = MoveCommand(getEngine(), x, y, type, uid, m_players_id[0]);
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
	
	//if (m_has_played || getEngine()->getPlayer(m_player_id).hasMoved(1)) {
	if(m_has_played){
		m_hud.updateMoveCapa(false);
	}
	else
	{
		m_hud.updateMoveCapa(true);
	} 
	if (m_has_played) {
	//if (m_has_played || getEngine()->getPlayer(m_player_id).hasAttacked(1)) {
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
	EndTurnCommand command = EndTurnCommand(getEngine(), m_players_id[0]);
	command.execute();
}

void Game::watchMovements()
{
	// Check moves for each player
	for(auto pl: getEngine()->getPlayers())
	{
		// check move for each unit
		for (std::map<int, bool>::iterator it = pl.second.getMovedBegin(); 
				it != pl.second.getMovedEnd();++it)
		{
			if(pl.second.hasMoved(it->first))
			{
				// Player has moved, request an animation
				LOG(DEBUG) << "Move asked";
				std::cout << m_move_watcher[pl.second.getId()];
				if(!m_move_watcher[pl.second.getId()] )
				{
					m_game_scene.addPendingMovement(pl.second.getId(), pl.second.getMove(pl.second.getId()));
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
	m_game_scene.getInfos()->disable();
}

void Game::enableActions()
{
	m_disable_actions = false;
	m_hud.actionsEnabled();
	m_game_scene.getInfos()->enable();
	
}