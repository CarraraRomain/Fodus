#include "IGame.hpp"

using namespace game;

IGame::IGame(boot::Bootstrap* boot, engine::AbstractEngine* engine, int cid): EngineObserver(engine, cid), m_boot(boot)
{
}

IGame::~IGame()
{
}

void IGame::connect(int pid)
{
	getEngine()->connect(pid);
}