#include "Subject.hpp"

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
