#include "Game.hpp"
#include "../render/Animation.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../engine/MoveCommand.hpp"
#include "../engine/EndTurnCommand.hpp"

using namespace game;

/*
Game::Game(Bootstrap* boot, Engine* eng) : Observer(&eng->getState()),
m_boot(boot), getEngine()(eng), m_hud(boot), m_isKeyPressed(false)
{
	m_client_id = rand();
	m_player_id = 1;
	LOG(DEBUG) << "Client ID: " << m_client_id;
}
*/


Game::Game(boot::Bootstrap* boot, engine::AbstractEngine* engine,
		   int cid): IGame(boot, engine, cid), m_hud(boot), m_game_scene(boot)
{
	m_has_played = false;
	m_end = false;
	m_disable_actions = true;
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
	m_select_box.setOutlineColor(sf::Color::Green);
	m_select_box.setFillColor(sf::Color::Transparent);
	m_select_box.setOutlineThickness(3);
	m_select_box.setSize(sf::Vector2f(SIZE, SIZE));
	m_show_box = false;
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
	//update(ObsState);
	m_player_playing = 1;
	LOG(DEBUG) << "Loop";
	while(m_game_window->isOpen())
	{
		if (m_end) m_game_window->close();

		if (m_player_playing == 1) game_event_loop();
		
		getEngine()->run();
		//handle_event();
		m_game_scene.updateAnims();
		reflowSkill();
		if (!m_game_scene.isAnimationRunning() && is_playing ) {
			enableActions();
		}else
		{
			disableActions();
		}
		
//		sf::Time frameTime = frameClock.restart();
		draw();
	}
	LOG(DEBUG) << "Game ended";
}

void Game::draw()
{
	m_game_window->clear();
	m_game_window->draw(m_hud);

	m_game_window->draw(m_game_scene);
	//if (m_disable_actions) m_game_window->draw(m_filter);
	if (m_show_box) m_game_window->draw(m_select_box);
	m_game_window->display();
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
	return;
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
			if (m_player_playing == m_players_id[0]) {
				is_playing = true;
				enableActions();
			}
			for (auto it : m_move_watcher) m_move_watcher[it.first] = false;
		}
		//watchMovements();
		std::vector<std::vector<int>> map = getEngine()->getMap(1);
		if(is_playing) m_game_scene.getInfos()->syncMoveMap(map);
		else m_game_scene.getInfos()->resetMoveMap();
		m_game_scene.update(m_list);

		break;
	}
	updateHUD();
}

void Game::updateGlobal(state::Etat& e)
{
	LOG(INFO) << "UPDATE : GLOBAL";
	if (e.getTurn() != m_turns)
	{
		LOG(DEBUG) << "New Turn!";
		m_turns = e.getTurn();
		m_hud.updateTurns(m_turns);
		is_playing = true;
		
	}

	std::vector<std::vector<int>> map = getEngine()->getMap(1);
	if (is_playing) m_game_scene.getInfos()->syncMoveMap(map);
	else m_game_scene.getInfos()->resetMoveMap();
	m_game_scene.update(*e.getList());
	updateHUD();
}

void Game::updateElement(state::Element& el)
{
}

void Game::updateTurn(int turn)
{
}

void Game::updatePlayer(engine::Player pl)
{
	LOG(DEBUG) << "Update: Player " << pl.getId();
	m_players.erase(pl.getId());
	m_players[pl.getId()] = pl;

	watchMovements(pl.getId());
}

void Game::updateGameEnd(int score)
{
	LOG(INFO) << "================";
	if(score > 0) LOG(INFO) << "YOU WON :)";
	else LOG(INFO) << "YOU LOST :(";
	LOG(INFO) << "Score: " << score;
	LOG(INFO) << "================";
	LOG(INFO) << "Fodus 2.Final";
	LOG(INFO) << "================";

	m_end = true;
}

void Game::updateNowPlaying(int pid)
{
	m_player_playing = pid;
	if (m_players_id[0] == pid)
	{
		is_playing = true;
		enableActions();
	}
}

void Game::canPlay(int pid)
{
}

void Game::hasPlayed(int pid)
{
}

void Game::sync(state::ElementList list)
{
}

void Game::syncRequest()
{
	//m_list = getEngine()->syncRequest();
	getEngine()->syncFull(m_players_id[0]);
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
			if(event.type == sf::Event::MouseMoved)
			{
				int x = event.mouseMove.x;
				int y = event.mouseMove.y;
				if (x >= OFFSET_X * SIZE && x < (OFFSET_X + WIDTH)*SIZE &&
					y >= OFFSET_Y * SIZE && y < (OFFSET_Y + HEIGHT)*SIZE)
				{
					m_select_box.setPosition(sf::Vector2f(SIZE* (x / SIZE),SIZE*( y / SIZE)));
					
					m_show_box = true;
				}
				else m_show_box = false;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
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
								engine::MoveCommand command = engine::MoveCommand(getEngine(), (x / SIZE), y / SIZE, MoveRight, 1, m_player_playing);
							command.execute();
							}
							else {
								engine::SkillCommand command = SkillCommand(getEngine(), (x / SIZE), y / SIZE, 1, skillMode-1, m_player_playing);
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
					skillMode = 1;
				}
				if (event.key.code == sf::Keyboard::Q)
				{
					skillMode = 0;
				}
				if (event.key.code == sf::Keyboard::A)
				{
					skillMode = 2;
				}
				if (event.key.code == sf::Keyboard::Z)
				{
					skillMode = 3;
				}

				if (move && !m_isKeyPressed)
				{
					engine::MoveCommand command = engine::MoveCommand(getEngine(), x, y, type, uid, m_players_id[0]);
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
	engine::Character ch = getEngine()->getPlayer(m_players_id[0])[1];
	if (m_has_played || ch.hasMoved()) {
	//if(m_has_played){
		m_hud.updateMoveCapa(false);
		m_game_scene.hideMoveMap();
	}
	else
	{
		m_hud.updateMoveCapa(true);
		m_game_scene.showMoveMap();
	} 
	//if (m_has_played) {
	if (m_has_played || ch.hasAttacked()) {
		m_hud.updateAttackCapa(false);
	}
	else
	{
		m_hud.updateAttackCapa(true);
	}

	m_hud.updateAction(skillMode);
}

void Game::endPlayerTurn()
{
	is_playing = false;
	disableActions();
	
	for (auto it : m_move_watcher)
	{
		LOG(DEBUG) << "Watcher: " << it.first << " : " << m_game_scene.isAnimationRunning(it.first);
		if (!m_game_scene.isAnimationRunning(it.first))
		{
			m_move_watcher[it.first] = false;
		}
	}
	draw();
	engine::EndTurnCommand command = EndTurnCommand(getEngine(), m_players_id[0]);
	command.execute();

}

void Game::watchMovements(int pid)
{

	LOG(DEBUG) << "Watching moves for pl " << pid;
	// Check moves for each player
	//for(auto pl: m_players)
	//{
	engine::Player pl = m_players[pid];
		// check move for each unit
		for (auto const &ch: pl)
		{
			LOG(DEBUG) << "Char " << ch.second->UID;
			LOG(DEBUG) << "Moved : " << ch.second->hasMoved();
			if(ch.second->hasMoved())
			{
				// Player has moved, request an animation
				LOG(DEBUG) << "Move asked";
				//std::cout << m_move_watcher[pl.second.getId()];
				if(!m_move_watcher[ch.second->UID])
				//if(!(ch.second->hasMoveWatch()))
				{
					m_game_scene.addPendingMovement(ch.second->UID, ch.second->getMoves());
					//ch.second->moveWatched();
					m_move_watcher[ch.second->UID] = true;
					
					disableActions();
				}
				
			}
		}
		for (auto it : m_move_watcher)
		{
			LOG(DEBUG) << "END Watcher: " << it.first << " : " << m_game_scene.isAnimationRunning(it.first);
		
		}
	//}

}

void Game::disableActions()
{
	if (m_disable_actions) return;
	LOG(INFO) << "Disabling actions";
	m_disable_actions = true;
	m_hud.actionsDisabled();
	m_game_scene.getInfos()->disable();
}

void Game::enableActions()
{
	if (!m_disable_actions) return;
	LOG(INFO) << "Enabling actions";
	m_disable_actions = false;
	m_hud.actionsEnabled();
	m_game_scene.getInfos()->enable();
	
}

void Game::reflowSkill()
{
	sf::Color cl;
	switch (skillMode)
	{
	case 1:
		cl = sf::Color::Red;
		break;
	case 2:
		cl = sf::Color::Yellow;
		break;
	case 3:
		cl = sf::Color::Blue;
		break;
	default:
		cl = sf::Color::Green;
		break;
	}
	m_select_box.setOutlineColor(cl);
	m_hud.updateAction(skillMode);
}

