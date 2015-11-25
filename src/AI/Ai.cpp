#include "Ai.hpp"



Ai::Ai()
{
}


Ai::~Ai()
{
}

void Ai::execute(int player_uid, Engine * engine)
{

	int i;
	for (i = 0; i < engine->getPlayer(player_uid).numberPersos(); i++)
	{
		/*int x = engine->getState().getAttribute("posX", engine->getPlayer(player_uid)[i]);
		int y = engine->getState().getAttribute("posY", engine->getPlayer(player_uid)[i]);
		MoveCommand commandM = MoveCommand(engine, x + 1, y + 1, MoveForward, engine->getPlayer(player_uid)[i], player_uid);
		commandM.execute();*/
		recherche1(engine->getState().getList(), player_uid, engine->getPlayer(player_uid)[i] , engine);
	}

	EndTurnCommand commandE = EndTurnCommand(engine, player_uid);
	commandE.execute();
}

void Ai::recherche1(ElementList* liste,int playerUid, int uid, Engine* engine)
{
	int i,j,x,y;
	int distanceMin = 0;
	int proche = 0;
	int attaqueDistance = 0;
	int okX = 0, okY = 0;

	engine->propagate(liste->getAttribute("posX", uid), liste->getAttribute("posY", uid), liste->getAttribute("move", uid), uid);

	for (i = 0; i < liste->size(); i++)
	{
		if ((*liste)[i]->getD() == 3 && liste->getAttribute("side",uid) != (*liste)[i]->getAttribute("side"))
		{
			x = liste->getAttribute("posX", uid) - liste->getAttribute("posX", (*liste)[i]->getUid());
			y = liste->getAttribute("posY", uid) - liste->getAttribute("posY", (*liste)[i]->getUid());
			if (x < 0)x = -x;
			if (y < 0)y = -y;
			
			if (x != 0 || y != 0)
			{
				distanceMin = x + y;
				proche = (*liste)[i]->getUid();
			}
		}
	}

	if (distanceMin > 0)
	{
		for (i = 0; i < WIDTH; i++)
		{
			for (j = 0; j < HEIGHT; j++)
			{
				if (engine->getMapValue(i, j, uid) > 0)
				{
					x = i - liste->getAttribute("posX", proche);
					y = j - liste->getAttribute("posY", proche);
					if (x < 0)x = -x;
					if (y < 0)y = -y;
					
					if (x + y <= liste->getAttribute("range", uid))
					{
						if (engine->getMapValue(i, j,uid) > attaqueDistance)
						{
							attaqueDistance = engine->getMapValue(i, j, uid);
							okX = i;
							okY = j;
						}
					}
					else
					{
						if (x + y < distanceMin && attaqueDistance < 1)
						{
							distanceMin = x + y;
							okX = i;
							okY = j;
						}
					}
				}
			}
		}
		if (okX > 0 || okY > 0) {
			MoveCommand commandM = MoveCommand(engine, okX, okY, MoveForward, uid, playerUid);
			commandM.execute();
		}
		if (attaqueDistance > 0)
		{
			AttackCommand commandA = AttackCommand(engine, uid, proche,playerUid);
			commandA.execute();
		}
	}
}