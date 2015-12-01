#pragma once
#include "../global.hpp"
#include "../engine/AttackCommand.h"
#include "../engine/MoveCommand.h"
#include "../engine/EndTurnCommand.hpp"
#include "../engine/Command.hpp"
#include "../engine/Engine.hpp"
#include "../state/Etat.hpp"
#include "../state/ElementList.hpp"

class Ai
{

public:
	Ai();
	~Ai();
	static void execute(int player_uid, AbstractEngine* engine);
	static void recherche1(ElementList*,int,int, AbstractEngine*);
};

