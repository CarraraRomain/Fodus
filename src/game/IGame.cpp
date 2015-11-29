#include "IGame.hpp"


IGame::IGame(Bootstrap* boot, AbstractEngine* engine, int cid): EngineObserver(engine, cid), m_boot(boot)
{
}

IGame::~IGame()
{
}

void IGame::connect(int pid)
{
	getEngine()->connect(pid);
}