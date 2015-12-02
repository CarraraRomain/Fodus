#pragma once
#include "Action.hpp"

class RestoreAction : public Action
{
private:
	int uid;
	int restore;
	int health;

public:
	virtual void execute(Etat& state) override;
	RestoreAction(int newUid, int restoreValue);
	~RestoreAction();
};