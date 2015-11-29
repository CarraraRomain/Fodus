#include "EngineObserver.hpp"


EngineObserver::EngineObserver(AbstractEngine* engine, int cid): m_engine(engine), CID(cid)
{
}

EngineObserver::~EngineObserver()
{
}

AbstractEngine* EngineObserver::getEngine()
{
	return m_engine;
}