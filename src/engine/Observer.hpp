#pragma once
#include "../global.hpp"
#include "Subject.hpp"
#include "../Enum.h"


class Observer
{
public:
	Observer(Subject* sub);
	~Observer();
	virtual void update(ObsType) = 0;
protected:
	Subject* getSubject();
	Subject* m_sub;

};
