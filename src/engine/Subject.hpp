#pragma once
#include "../global.hpp"

class Observer;

class Subject
{
public:
	Subject();
	~Subject();
	void attach(Observer*);
	void notify();

private:
	std::vector<Observer*> m_obs;

};

