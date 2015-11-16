#pragma once
#include "../global.hpp"
#include "Subject.hpp"


class Observer
{
public:
	Observer(Subject* sub);
	~Observer();
	virtual void update() = 0;
protected:
	Subject* getSubject();
	Subject* m_sub;

};

