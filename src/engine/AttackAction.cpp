#include "AttackAction.h"

void AttackAction::execute(Etat* attack)
{
	posX1 = attack->getAttribute("posX", uid1);
	posY1 = attack->getAttribute("posY", uid1);
	posX2 = attack->getAttribute("posX", uid2);
	posY2 = attack->getAttribute("posY", uid2);
	scope = attack->getAttribute("scope", scope);

	if (uid2 == 0)
		LOG(DEBUG) << "can't be attacked";
	else
		if (abs(posX1 - posX2) + abs(posY1 - posY2) > scope)
			LOG(DEBUG) << "attack is out of range";
}