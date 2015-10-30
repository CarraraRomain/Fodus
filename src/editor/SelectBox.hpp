#pragma once

#include <SFML/Graphics.hpp>

#include "../global.hpp"
class SelectBox: public sf::Drawable
{
public:
	SelectBox();
	~SelectBox();
	void setStart(sf::Vector2i);
	sf::Vector2i getStart() const;
	void setCurrent(sf::Vector2i);
	sf::Vector2i getCurrent() const;
	void setEnd(sf::Vector2i);
	sf::Vector2i getEnd() const;
	void active();
	void inactive();
	bool isActive();
	virtual void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;
	void setBox();

private:
	sf::Vector2i m_start;
	sf::Vector2i m_current;
	sf::Vector2i m_end;
	sf::RectangleShape m_box;
	bool m_active;
	sf::Vector2i SelectBox::checkBoundaries(sf::Vector2i& vect);
	void checkOrder();
};

