#pragma once 

#include "../state/Etat.hpp"
#include "../state/ElementList.hpp"
#include "Command.hpp"
#include "MoveCommand.h"
#include "MoveAction.hpp"
#include "DeadAction.h"
#include "DamageAction.hpp"
#include "EndGameAction.hpp"
#include "StatusAction.hpp"
#include "RestoreAction.hpp"
#include "ActionList.hpp"
#include "SkillCommand.hpp"
class Engine;

class Ruler
{
public :
	Ruler(Engine* e, Etat& state);
	~Ruler();
	void execute(Command* com, Etat* state);
	void update();
	bool checkMove(Etat* state, int x, int y, int uid, int player);
	bool createMove(Etat* state, int x, int y, int uid, int player);
	bool checkAttack(Etat* state, int uid1, int uid2, int player);
	bool createAttack(Etat* state, int uid1, int uid2);
	int checkSkill(Etat* state, int posX, int posY, int uid, int skillIndex, int player);
	bool createSkill(Etat* state, int uid, int index, int posX, int posY, int target);
	void createMap(Etat* state);
	void createMapCharacter(int uid);
	void propagate(int posX, int posY, int value, int uid);
	void nextPlayer(int played, int toPlay, Etat* state);
	int getMapValue(int x, int y, int uid);
	std::vector< std::vector<int> > getMap(int uid);
	void checkRule(Etat* state);
	void EndTurnRule(int played, Etat* state);

private:
	Etat& m_state;
	std::unique_ptr<ActionList> m_action_list;
	std::vector< std::vector<int> > map;
	std::map < int, std::vector< std::vector<int> > > mapCharacter;
	bool m_end;
	Engine* m_engine;
};

