#pragma once
#include "Action.hpp"


class SpawnAction : public Action
{
public :
	SpawnAction(Perso* newPerso);
	~SpawnAction();
	virtual void execute(Etat& state) override;

private :
	Perso* persoSpawned;
};

