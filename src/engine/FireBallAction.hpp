#pragma once
#include "Action.hpp"

class FireBallAction : public Action
{
private:
	int power, currentHealth;
	int uid1, uid2;

public:
	virtual void execute(Etat& state) override;
	FireBallAction(int uid1, int power, int uid2, int currentHealth);
	~FireBallAction();
};