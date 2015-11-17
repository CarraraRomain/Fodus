#include "../state/Etat.hpp"
#include "../state/ElementList.hpp"
#include "Command.hpp"
#include "MoveCommand.h"
#include "MoveAction.hpp"
#include "DamageAction.hpp"
#include "ActionList.hpp"

class Engine;

class Ruler
{
public :
	Ruler(Etat& state);
	~Ruler();
	void execute(Command* com, Etat* state);
	void update();
	bool checkMove(Etat* state, int x, int y, int uid);
	bool createMove(Etat* state, int x, int y, int uid);
	bool checkAttack(Etat* state, int uid1, int uid2);
	bool createAttack(Etat* state, int uid1, int uid2);
	void createMap(Etat* state);
	void propagate(int posX, int posY, int value);
	void nextPlayer();

private:
	Etat& m_state;
	std::unique_ptr<ActionList> m_action_list;
	std::vector< std::vector<int> > map;
	std::vector< std::vector<int> > mapCharacter;

	int moveDone;
	int attackDone;
};

