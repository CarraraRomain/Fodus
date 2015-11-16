#pragma once
#include "../global.hpp"

class Observer;

class Subject
{
public:
	Subject();
	~Subject();
	void attach(Observer*);
	virtual void notify() = 0;

protected:
	std::vector<Observer*> m_obs;

};

