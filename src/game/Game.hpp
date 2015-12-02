#pragma once

/*
* SFML
*/
#include <SFML/Graphics.hpp>

#include "../bootstrap/Bootstrap.hpp"
#include "../render/Scene.hpp"
#include "../engine/Engine.hpp"

#include "../engine/Observer.hpp"

#include "HUD.hpp"
#include "Coord.hpp"
#include "IGame.hpp"

class Game: public IGame
{
public:
	Game(Bootstrap*, AbstractEngine* engine, int cid);
	~Game();
	void load_gui();
	void load();
	void run();
	void start();
	void syncRequest() override;
	void whoIsPlaying() override;
	void update(ObsType) override;
	void updateGlobal(Etat& e)	 override;
	void updateElement(Element& el) override;
	void updateTurn(int turn)  override;
	void updatePlayer(Player pl) override;
	void updateNowPlaying(int pid)  override;
	void canPlay(int pid) 	 override;
	void hasPlayed(int pid) override;
	void sync(ElementList list) override;
private:
	
	// Graphics
	std::unique_ptr<sf::RenderWindow> m_game_window;
	HUD m_hud;
	Scene m_game_scene;
	//

	std::unique_ptr<rapidjson::Document> m_game_level;
	
	Perso* m_selected_perso;

	int m_client_id;
	// old
	bool m_isKeyPressed;
	int m_turns;
	std::map<int, bool> m_move_watcher;

	bool m_has_played;
	bool is_playing;
	void game_event_loop();
	void updateHUD();
	void endPlayerTurn();
	void watchMovements();
	void disableActions();
	void enableActions();

	int skillMode;
};

