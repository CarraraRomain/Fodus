#include "Animation.hpp"



Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::addFrame(sf::IntRect frame)
{
	m_frames.push_back(frame);
}

void Animation::setTexture(const sf::Texture& text)
{
	m_texture = &text;
}

const sf::Texture* Animation::getTexture() const
{
	return m_texture;
}

std::size_t Animation::getSize() const
{
	return m_frames.size();
}

const sf::IntRect& Animation::getFrame(std::size_t n) const
{
	return m_frames[n];
}