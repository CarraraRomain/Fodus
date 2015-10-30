#include "SelectBox.hpp"
#include <iostream>


SelectBox::SelectBox()
{
	m_box = sf::RectangleShape();
	m_box.setOutlineColor(sf::Color::Red);
	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);
	m_active = false;
}


SelectBox::~SelectBox()
{
}

void SelectBox::setStart(sf::Vector2i vect)
{
	m_start = checkBoundaries(vect);
	std::cout << "Start X " << m_start.x;
	std::cout << ", Start Y " << m_start.y << std::endl;
}

sf::Vector2i SelectBox::getStart() const
{
	return m_start;
}

void SelectBox::setCurrent(sf::Vector2i vect)
{

	m_current.x = vect.x - m_start.x;
	m_current.y = vect.y - m_start.y;
	if (m_current.x >= 0) m_current.x = m_current.x + 1;
	else m_current.x = m_current.x - 1 ;
	if (m_current.y >= 0) m_current.y = m_current.y + 1;
	else m_current.y = m_current.y - 1;
	// No boundaries check here (will be done in setEnd)
	//m_current = checkBoundaries(m_current);

	std::cout << "Cur X " << m_current.x;
	std::cout << ", Cur Y " << m_current.y << std::endl;
}

sf::Vector2i SelectBox::getCurrent() const
{
	return m_current;
}

void SelectBox::setEnd(sf::Vector2i vect)
{
	m_end = checkBoundaries(vect);
	checkOrder();
	std::cout << "End X " << m_end.x;
	std::cout << ", End Y " << m_end.y << std::endl;
}

sf::Vector2i SelectBox::getEnd() const
{
	return m_end;
}

void SelectBox::active()
{
	m_active = true;
}

void SelectBox::inactive()
{
	m_active = false;
}

bool SelectBox::isActive()
{
	return m_active;
}

void SelectBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(m_active) target.draw(m_box, states);
}

void SelectBox::setBox()
{
	int draw_x;
	int draw_y;
	draw_x = (m_current.x < 0) ? m_start.x + 1 : m_start.x;
	draw_y = (m_current.y < 0) ? m_start.y + 1 : m_start.y;

	m_box.setSize(sf::Vector2f(float(m_current.x*SIZE), float(m_current.y*SIZE)));
	m_box.setPosition(draw_x*SIZE, draw_y*SIZE);
}

sf::Vector2i SelectBox::checkBoundaries(sf::Vector2i& vect)
{
	// Check boundaries
	vect.x = (vect.x >= WIDTH) ? WIDTH - 1 : vect.x;
	vect.x = (vect.x <  0) ? 0 : vect.x;
	vect.y = (vect.y >= HEIGHT) ? HEIGHT - 1 : vect.y;
	vect.y = (vect.y <  0) ? 0 : vect.y;
	return vect;
}

void SelectBox::checkOrder()
{
	if (m_end.x < m_start.x)
	{
		int tmp = m_end.x;
		m_end.x = m_start.x;
		m_start.x = tmp;
	}
	if (m_end.y < m_start.y)
	{
		int tmp = m_end.y;
		m_end.y = m_start.y;
		m_start.y = tmp;
	}
}