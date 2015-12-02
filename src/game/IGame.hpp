#pragma once
#include "../global.hpp"
#include "EngineObserver.hpp"
#include "../bootstrap/Bootstrap.hpp"
#include "HUD.hpp"
#include "../render/Scene.hpp"

class IGame :
	public EngineObserver
{
public:
	IGame(Bootstrap* boot, AbstractEngine* engine, int cid);
	~IGame();
	void connect(int pid);
	virtual void syncRequest() = 0;
	virtual void whoIsPlaying() = 0;
protected:
	// Misc
	Bootstrap* m_boot;
	ElementList m_list;
	std::map<int, Player> m_players;
	std::vector<int> m_players_id;
	int m_player_playing;
	bool m_disable_actions;
};

