#include "Ai.hpp"



Ai::Ai()
{
}


Ai::~Ai()
{
}

void Ai::execute(int player_uid, Engine * engine)
{
	// command1 = MoveCommand(engine, 2, 3, MoveForward, player_uid, player_uid);

	int i;
	for (i = 0; i < engine->getPlayer(player_uid).numberPersos(); i++)
	{
		int x = engine->getState().getAttribute("posX", engine->getPlayer(player_uid)[i]);
		int y = engine->getState().getAttribute("posY", engine->getPlayer(player_uid)[i]);
		MoveCommand commandM = MoveCommand(engine, x + 1, y + 1, MoveForward, engine->getPlayer(player_uid)[i], player_uid);
		commandM.execute();
	}

	EndTurnCommand command = EndTurnCommand(engine, player_uid);
	command.execute();
}
