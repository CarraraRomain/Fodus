#include "Game.hpp"
#include "../render/Animation.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../engine/MoveCommand.h"


Game::Game(Bootstrap* boot) : m_boot(boot), m_isKeyPressed(false)
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
	m_game_engine.reset(new Engine);
}

void Game::run()
{
	LOG(DEBUG) << "Game is running";
	
	LegacyElementList list;
	TestGame::test_load_elt_list(&list, m_boot);
	load();
	LOG(DEBUG) << "Updating";
	Perso* elt = new Perso();
	elt->setAttribute("deplacement", 10);
	elt->setX(10);
	elt->setY(10);
	elt->setD(0);
	elt->setKey("MLP");
	m_game_engine->getState().getList()->push_back(elt);
	// set up AnimatedSprite
	AnimatedSprite animatedSprite(sf::seconds(0.2), true);
	animatedSprite.setPosition(sf::Vector2f(float(SIZE*WIDTH / 2),
		float(SIZE*HEIGHT / 2)));
	m_game_scene->addSprite(animatedSprite);
	sf::Clock frameClock;
	AnimationType type = MoveForward;
	float speed = 80.f;
	bool noKeyWasPressed = true;
	m_game_scene->update(list);
	LOG(DEBUG) << "Loop";
	while(m_game_window->isOpen())
	{
		game_event_loop();
		handle_keys();

//		sf::Time frameTime = frameClock.restart();
//		// if a key was pressed set the correct animation and move correctly
//		sf::Vector2f movement(0.f, 0.f);
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//		{
//			type = MoveForward;
//			movement.y = speed;
//			noKeyWasPressed = false;
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//		{
//			type = MoveBackward;
//			movement.y += speed;
//			noKeyWasPressed = false;
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//		{
//			type = MoveLeft;
//			movement.x -= speed;
//			noKeyWasPressed = false;
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//		{
//			type = MoveRight;
//			movement.x += speed;
//			noKeyWasPressed = false;
//		}
//		animatedSprite.play(type);
//		animatedSprite.move(movement * frameTime.asSeconds());
//		if (noKeyWasPressed)
//		{
//			animatedSprite.stop();
//		}
//		noKeyWasPressed = true;
//
//		// update AnimatedSprite
//		animatedSprite.update(frameTime);
		m_game_window->clear();
		m_game_window->draw(*m_game_scene);
		m_game_window->draw(animatedSprite);
		m_game_window->display();
	}
	LOG(DEBUG) << "Game ended";
}

void Game::handle_keys()
{
	bool move = false;
	int x(0), y(0), uid(42);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		move = true;
		x = 1;
		y = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		move = true;
		x = -1;
		y = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		move = true;
		x = 0;
		y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		move = true;
		x = 0;
		y = 1;
	
	}

	if (move && !m_isKeyPressed)
	{
		MoveCommand command = MoveCommand(m_game_engine.get(), x, y, uid);
		command.execute();
		m_isKeyPressed = true;
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

