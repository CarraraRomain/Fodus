#pragma once
#include "../global.hpp"

class Animation
{
public:
	Animation();
	~Animation();

	void addFrame(sf::IntRect);
	void setTexture(const sf::Texture&);
	const sf::Texture* getTexture() const;
	std::size_t getSize() const;
	const sf::IntRect& getFrame(std::size_t) const;

private:
	std::vector<sf::IntRect> m_frames;
	const sf::Texture* m_texture;
};

