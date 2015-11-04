#include "Game.hpp"



Game::Game(Bootstrap* boot) : m_boot(boot)
{
}


Game::~Game()
{
}

void Game::load_gui()
{
	LOG(DEBUG) << "Loading GUI";
	m_game_scene.reset(new Scene(m_boot));
	m_game_window.reset(new sf::RenderWindow(sf::VideoMode(SIZE*WIDTH,
		SIZE*HEIGHT), "Level", sf::Style::Titlebar | sf::Style::Close));
}

void Game::load()
{
	load_gui();
}

void Game::run()
{
	LOG(DEBUG) << "Game is running";
	load();
	LegacyElementList list;
	TestGame::test_load_elt_list(&list, m_boot);
	LOG(DEBUG) << "Updating";
	m_game_scene->update(list);
	LOG(DEBUG) << "Loop";
	while(m_game_window->isOpen())
	{
		game_event_loop();
	}
	LOG(DEBUG) << "Game ended";
}

void Game::game_event_loop()
{
	sf::Event Event;
	while (m_game_window->pollEvent(Event)) {
		if (Event.type == sf::Event::Closed)
			m_game_window->close();
	}
	m_game_window->clear();

	m_game_window->draw(*m_game_scene);

	m_game_window->display();

}

