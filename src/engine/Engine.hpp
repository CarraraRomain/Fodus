#pragma once

#include "../state/Etat.hpp"
//#include "CommandeListe.hpp"
#include "Ruler.hpp"
#include "AbstractEngine.hpp"
#include "../test/game/TestGame.hpp"
#include "Player.hpp"

class Engine: public AbstractEngine
{
public:
	Engine(Bootstrap*);
	void handleCommand(Command*) override;
	void run();
	Etat& getState() override;
	int registerPlayer(int client, int player) override;
	int connect(int client) override;
	void start() override;
	Player& getPlayer(int);
protected:
	int registerPlayer(int player) override;

private :
	Bootstrap* m_boot;
	std::unique_ptr<Etat> state;
	//CommandeListe liste;
	std::vector<int> m_has_played;
	std::unique_ptr<Ruler> m_ruler;
	std::map<int, Player> m_players;
	void nextPlayer(int played);
	void nextTurn();
};