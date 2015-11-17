#pragma once
#include "../state/Etat.hpp"
#include "CommandReceiver.hpp"

class AbstractEngine: public CommandReceiver
{
public:
	AbstractEngine();
	~AbstractEngine();
	virtual Etat& getState() = 0;
	virtual int registerPlayer(int client, int player) = 0;
	virtual int connect(int client) = 0;
	virtual void start() = 0;


protected:
	std::map<int, int> m_clients_players;
	std::vector<int> m_clients;
	int m_player_playing;
	virtual int registerPlayer(int player) = 0;
};


