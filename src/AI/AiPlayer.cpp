#include "AiPlayer.hpp"



AiPlayer::AiPlayer(Bootstrap* boot, AbstractEngine* engine, int cid) : IGame(boot, engine, cid)
{
}


AiPlayer::~AiPlayer()
{
}

void AiPlayer::run()
{
	int i;
	for (i = 0; i < getEngine()->getPlayer(m_player_playing).numberPersos(); i++)
	{
		recherche1(getEngine()->getState().getList(), m_player_playing, getEngine()->getPlayer(m_player_playing)[i], getEngine());
	}

	EndTurnCommand commandE = EndTurnCommand(getEngine(), m_player_playing);
	commandE.execute();
}

void AiPlayer::start()
{
	// This Client has Player 1 (Human) and player 2 (IA)
	m_players_id.push_back(2);

		int rc = getEngine()->connect(2);
		if (rc >= 400) LOG(FATAL) << "Cannot connect to engine: " << rc;
		rc = getEngine()->registerPlayer(2, this);
		if (rc >= 400) LOG(FATAL) << "Cannot register to engine: " << rc;


	LOG(DEBUG) << "Connected to local, CID: " << "???" << ", PID: " << m_players_id[0];

}

void AiPlayer::syncRequest()
{
	m_list = getEngine()->syncRequest();
}

void AiPlayer::whoIsPlaying()
{
	m_player_playing = getEngine()->whoIsPlaying();
}

void AiPlayer::update(ObsType)
{
}

void AiPlayer::updateGlobal(Etat & e)
{
}

void AiPlayer::updateElement(Element & e1)
{
}

void AiPlayer::updateTurn(int turn)
{
}

void AiPlayer::updateNowPlaying(int pid)
{
	m_player_playing = pid;
	if (m_players_id[0] == pid) run();
}

void AiPlayer::canPlay(int pid)
{
}

void AiPlayer::hasPlayed(int pid)
{
}

void AiPlayer::sync(ElementList list)
{
}

void AiPlayer::recherche1(ElementList* liste, int playerUid, int uid, AbstractEngine* engine)
{
	int i, j, x, y;
	int distanceMin = 0;
	int proche = 0;
	int attaqueDistance = 0;
	int okX = 0, okY = 0;

	engine->propagate(liste->getAttribute("posX", uid), liste->getAttribute("posY", uid), liste->getAttribute("move", uid), uid);

	if (liste->getAttribute("currentHealth", uid) < liste->getAttribute("health", uid) / 2)
	{
		behavior = Fear;
	}
	else behavior = Aggression;

	for (i = 0; i < liste->size(); i++)
	{
		if ((*liste)[i]->getD() == 3 && liste->getAttribute("side", uid) != (*liste)[i]->getAttribute("side"))
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

					if (x + y <= liste->getAttribute("range", uid) && behavior == Aggression)
					{
						if (engine->getMapValue(i, j, uid) > attaqueDistance)
						{
							attaqueDistance = engine->getMapValue(i, j, uid);
							okX = i;
							okY = j;
						}
					}
					else
					{
						if ((x + y < distanceMin && behavior != Fear) || (x + y > distanceMin && behavior == Fear) && attaqueDistance < 1)
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
			AttackCommand commandA = AttackCommand(engine, uid, proche, playerUid);
			commandA.execute();
		}
	}
}