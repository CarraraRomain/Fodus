#include "AbstractEngine.hpp"

#include "../game/EngineObserver.hpp"


AbstractEngine::AbstractEngine(): m_player_playing(1)
{
}


AbstractEngine::~AbstractEngine()
{
}

void AbstractEngine::notifyGlobal()
{
	std::vector<int> notified;
	for (auto obs : m_players_obs)
	{
		if (std::find(notified.begin(), notified.end(), obs.second->CID) == notified.end())
		{
			LOG(DEBUG) << "Notify";
			obs.second->updateGlobal(getState());
			obs.second->updatePlayer(m_players[current_player_uid]);
			m_players[current_player_uid].resetMoves();
			notified.push_back(obs.second->CID);
		}
		LOG(INFO) << "Already notified";
	}
	//notifyPlayer(m_players[current_player_uid]);
	LOG(INFO) << "=== END NOTIFY ===";
}

void AbstractEngine::notifyElement(Element& el)
{
	for (auto obs : m_players_obs) obs.second->updateElement(el);
}

void AbstractEngine::notifyTurn(int turn)
{
	for (auto obs : m_players_obs) obs.second->updateTurn(turn);
}

void AbstractEngine::notifyNowPlaying(int pid)
{
	std::vector<int> notified;
	for (auto obs : m_players_obs)
		{
			if (std::find(notified.begin(), notified.end(), obs.second->CID) == notified.end())
			{
				obs.second->updateNowPlaying(pid);
				notified.push_back(obs.second->CID);
			}
		}
}

void AbstractEngine::notifyCanPlay(int pid)
{
	m_players_obs[pid]->canPlay(pid);
}

void AbstractEngine::notifyPlayer(Player pl)
{
	std::vector<int> notified;
	for (auto obs : m_players_obs)
	{
		if (std::find(notified.begin(), notified.end(), obs.second->CID) == notified.end())
		{
			obs.second->updatePlayer(pl);
			notified.push_back(obs.second->CID);
		}
	}
}

void AbstractEngine::notifyHasPlayed(int pid)
{
	m_players_obs[pid]->hasPlayed(pid);
}
