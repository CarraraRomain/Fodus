#pragma once
#include "../engine/AbstractEngine.hpp"

class EngineObserver
{
public:
	EngineObserver(AbstractEngine* engine, int cid);
	~EngineObserver();
	virtual void update(ObsType) = 0;
	virtual void updateGlobal() = 0;
	virtual void updateElement(Element* el) = 0;
	virtual void updateTurn(int turn) = 0;
	virtual void updateNowPlaying(int pid) = 0;
	virtual void canPlay(int pid) = 0;
	virtual void hasPlayed(int pid) = 0;
	virtual void sync(ElementList list) = 0;
protected:
	AbstractEngine* getEngine();
	const int CID;
private:
	AbstractEngine* m_engine;
};

