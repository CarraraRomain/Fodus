#include "Game.hpp"



Game::Game(Bootstrap* boot) : m_boot(boot)
{
}


Game::~Game()
{
}

void Game::load_gui()
{
	m_game_scene.reset(new Scene(JSON_TILES_INDEX));
	m_game_window.reset(new sf::RenderWindow(sf::VideoMode(SIZE*WIDTH,
		SIZE*HEIGHT), "Level", sf::Style::Titlebar | sf::Style::Close));
}

void Game::load()
{
	load_gui();
}

void Game::run()
{
	load();
	ElementList list;
	TestGame::test_load_elt_list(&list);
	m_game_scene->update(list);
	while(m_game_window->isOpen())
	{
		game_event_loop();
	}
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

