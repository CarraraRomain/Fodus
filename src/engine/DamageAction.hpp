#pragma once
#include "Action.hpp"

class DamageAction : public Action
{
private:
	int uid;
	int damage;

public:
	virtual void execute(Etat& state) override;
	DamageAction(int uid, int value);
	~DamageAction();
};