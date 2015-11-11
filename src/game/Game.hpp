#pragma once

/*
* SFML
*/
#include <SFML/Graphics.hpp>

#include "../bootstrap/Bootstrap.hpp"
#include "../render/Scene.hpp"
#include "../engine/Engine.hpp"

#include "../test/game/TestGame.hpp"

class Game
{
public:
	Game(Bootstrap*);
	~Game();
	void load_gui();
	void load();
	void run();


private:
	Bootstrap* m_boot;
	std::unique_ptr<Engine> m_game_engine;
	std::unique_ptr<sf::RenderWindow> m_game_window;
	std::unique_ptr<Scene> m_game_scene;

	std::unique_ptr<rapidjson::Document> m_game_level;
	bool m_isKeyPressed;
	void handle_keys();
	void game_event_loop();
};

