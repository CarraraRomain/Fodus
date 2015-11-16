#pragma once
#include "../global.hpp"
#include "Subject.hpp"


class Observer
{
public:
	Observer(Subject* sub): m_sub(sub)
	{
		m_sub->attach(this);
	}
	~Observer();
	virtual void update() = 0;
protected:
	Subject* getSubject();
private:
	Subject* m_sub;

};

