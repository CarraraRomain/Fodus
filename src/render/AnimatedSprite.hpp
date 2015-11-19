#pragma once
#include "../global.hpp"
#include "Animation.hpp"

class AnimatedSprite: public sf::Drawable, public sf::Transformable
{
public:
	~AnimatedSprite();
	explicit AnimatedSprite(sf::Time frameTime = sf::seconds(0.2f),
		bool paused = false, int row = 42);

	void update(sf::Time deltaTime);
	void setAnimation(int i);
	void setType(AnimationType type);
	void loadAnimation(int row);
	void setFrameTime(sf::Time time);
	void play();
	void play(AnimationType type);
	void pause();
	void stop();
	Animation getAnimation() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	bool isPlaying() const;
	sf::Time getFrameTime() const;
	void setFrame(std::size_t newFrame, bool resetTime = true);

private:
	bool init;
	Animation m_animation;
	AnimationType m_type;
	std::unique_ptr<Animation> m_animations[4];
	sf::Time m_frameTime;
	sf::Time m_currentTime;
	std::size_t m_currentFrame;
	sf::Texture m_texture;
	sf::Vertex m_vertices[4];
	bool m_isPaused;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

