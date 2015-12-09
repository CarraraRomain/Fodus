#include "Observer.hpp"

using namespace engine;

Observer::Observer(Subject* sub): m_sub(sub)
{
	m_sub->attach(this);
}

Observer::~Observer()
{
}

Subject* Observer::getSubject()
{
	return m_sub;
}