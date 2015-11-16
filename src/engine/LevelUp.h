#pragma once
#include "Action.hpp"

class LevelUp : public Action
{
private:
	int uid;
	int health;
	int defence;
	int power;
	int limitZombie;
	int level;

public:
	void execute(Etat* state);
};