#pragma once
#include "../state/Etat.hpp"
#include "CommandReceiver.hpp"
#include "Player.hpp"
//#include "../game/EngineObserver.hpp"

class EngineObserver;

class AbstractEngine: public CommandReceiver
{
public:
	AbstractEngine();
	~AbstractEngine();
	virtual Etat& getState() = 0;
	virtual int registerPlayer(int player, EngineObserver*) = 0;
	virtual int connect(int client) = 0;
	virtual void start() = 0;
	virtual void run() = 0;
	virtual ElementList syncRequest() = 0;
	virtual int whoIsPlaying() = 0;
	virtual std::vector< std::vector<int> > getMap(int uid) = 0;
	virtual std::map<int, Player>& getPlayers() = 0;
	////////////////////////////////
	// backward compatibility methods
	// TODO TO REMOVE
	virtual Player& getPlayer(int) = 0;
	virtual void propagate(int x, int y, int valeur, int uid) = 0;
	virtual int getMapValue(int x, int y, int uid) = 0;
	////////////////////////////////
protected:
	std::map<int, int> m_clients_players;
	std::vector<int> m_clients;
	std::map<int, EngineObserver*> m_players_obs;
	std::map<int, Player> m_players; 
	int m_player_playing;
	int current_player_uid;
	virtual int registerPlayer(int player) = 0;
	virtual void notifyGlobal();
	virtual void notifyElement(Element& el);
	virtual void notifyTurn(int turn);
	virtual void notifyNowPlaying(int pid);
	virtual void notifyCanPlay(int pid);
	virtual void notifyPlayer(Player pl);
	virtual void notifyHasPlayed(int pid);

};


