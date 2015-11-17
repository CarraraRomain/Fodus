#pragma once
#include "Action.hpp"

class DamageAction : public Action
{
private:
	int uid1, uid2;
	int power1;
	int defence2;
	int currentHealth2;
	int damage;

public:
	void execute(Etat* state);
	DamageAction(int uid1, int uid2, int value);
	~DamageAction();
};