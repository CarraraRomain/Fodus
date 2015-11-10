#include "../state/Etat.hpp"
#include "../state/ElementList.hpp"
#include "Command.hpp"

class Ruler
{
public :
	void execute(Command* com, Etat* state);
	bool checkMove(Etat* state, int posX, int posY, int uid);
	bool checkAttack(Etat* state, int uid1, int uid2);
};

