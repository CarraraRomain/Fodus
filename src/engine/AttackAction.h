#pragma once
#include "Action.hpp"

class AttackAction : public Action
{
private:
	int uid1, uid2;
	int posX1, posY1, posX2, posY2;
	int scope;

public:
	void execute(Etat* attack);
};