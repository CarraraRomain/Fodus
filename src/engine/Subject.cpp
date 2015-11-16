#include "Subject.hpp"

#include "Observer.hpp"

Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::attach(Observer* obs)
{
	m_obs.push_back(obs);
}

void Subject::notify()
{
	for(auto obs: m_obs)
	{
		obs->update();
	}
}