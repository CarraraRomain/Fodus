#include "Element.hpp"

using namespace state;

Element::~Element()
{
}

void Element::setX(int newX)
{
	m_x = newX;
}
int Element::getX()
{
	return m_x;
}

void Element::setY(int newY)
{
	m_y = newY;
}
int Element::getY()
{
	return m_y;
}

void Element::setD(int newD)
{
	m_d= newD;
}
int Element::getD()
{
	return m_d;
}

void Element::setKey(std::string key)
{
	m_key = key;
}

std::string Element::getKey()
{
	return m_key;
}

/*bool Element::isGround()
{
	return false;
}

bool Element::isAllie()
{
	return false;
}

bool Element::isNeutral()
{
	return false;
}

bool Element::isEnnemy()
{
	return false;
}*/

int Element::getUid()
{
	return uid;
}

ElementType Element::getType() {
	return type;
}

void Element::setClasse(Classe c) {
	classe = c;
}

const Classe Element::getClasse() const {
	return classe;
}

Element::Element(int id, ElementType type): type(type), uid(id)  {

}
