#include "LegacyElement.hpp" 

void LegacyElement::setX(int newX)
{
	m_x = newX;
}
int LegacyElement::getX()
{
	return m_x;
}

void LegacyElement::setY(int newY)
{
	m_y = newY;
}
int LegacyElement::getY()
{
	return m_y;
}

void LegacyElement::setD(int newD)
{
	m_d= newD;
}
int LegacyElement::getD()
{
	return m_d;
}

void LegacyElement::setKey(std::string key)
{
	m_key = key;
}

std::string LegacyElement::getKey()
{
	return m_key;
}

bool LegacyElement::isGround()
{
	return false;
}

bool LegacyElement::isPerso()
{
	return false;
}

bool LegacyElement::isAllie()
{
	return false;
}

bool LegacyElement::isNeutral()
{
	return false;
}

bool LegacyElement::isEnnemy()
{
	return false;
}

int LegacyElement::getUid()
{
	return uid;
}