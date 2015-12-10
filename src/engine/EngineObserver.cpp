#include "EngineObserver.hpp"

using namespace engine;

EngineObserver::EngineObserver(engine::AbstractEngine* engine, int cid): m_engine(engine), CID(cid)
{
}

EngineObserver::~EngineObserver()
{
}

engine::AbstractEngine* EngineObserver::getEngine()
{
	return m_engine;
}