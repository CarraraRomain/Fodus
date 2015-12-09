#include "Subject.hpp"

using namespace engine;

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
