#pragma once

/*
* SFML
*/
#include <SFML/Graphics.hpp>

#include "../bootstrap/Bootstrap.hpp"
#include "../render/Scene.hpp"
#include "../engine/Engine.hpp"

#include "../test/game/TestGame.hpp"
#include "../engine/Observer.hpp"

#include "../AI/Ai.hpp"

class Game: public Observer
{
public:
	Game(Bootstrap*, Engine*);
	~Game();
	void load_gui();
	void load();
	void run();
	void update(ObsType) override;

private:
	Bootstrap* m_boot;
	Engine* m_game_engine;
	bool m_has_played;
	std::unique_ptr<sf::RenderWindow> m_game_window;
	std::unique_ptr<Scene> m_game_scene;
	sf::Font m_font;
	std::unique_ptr<rapidjson::Document> m_game_level;
	bool m_isKeyPressed;
	int m_turns;
	std::map<int, bool> m_move_watcher;
	sf::Text t_turns;
	sf::Texture m_dashboard_texture;
	sf::RectangleShape m_dashboard;
	int m_client_id;
	int m_player_id;
	void game_event_loop();
	void test_hud();
	void endPlayerTurn();
	void watchMovements();
};

