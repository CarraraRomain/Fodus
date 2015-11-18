#include "AnimatedSprite.hpp"


AnimatedSprite::~AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(sf::Time frameTime, bool paused, int row) :
	m_frameTime(frameTime), m_currentFrame(0), m_isPaused(paused)
{
	sf::Image image;
	if (!image.loadFromFile("../../res/GFX/Sprites2.png"))
	{
		LOG(FATAL) << "Cannot load sprites";
		return;
	}
	image.createMaskFromColor(sf::Color::Black);
	m_texture.loadFromImage(image);
	loadAnimation(row);
}

void AnimatedSprite::setAnimation(int i)
{
	m_animation = *(m_animations[i]);
	m_currentFrame = 0;
	setFrame(m_currentFrame);
}

void AnimatedSprite::setType(AnimationType type)
{
	m_type = type;
}

void AnimatedSprite::setFrameTime(sf::Time time)
{
	m_frameTime = time;
}

void AnimatedSprite::play()
{
	m_isPaused = false;
}

void AnimatedSprite::play(AnimationType type)
{
	int i = 0;
	
	switch(m_type)
	{
	case MoveForward:
		i = 0;
		break;
	case MoveBackward:
		i = 1;
		break;
	case MoveLeft:
		i = 2;
		break;
	case MoveRight:
		i = 3;
		break;
	}
	 setAnimation(i);
	
	play();
}

void AnimatedSprite::pause()
{
	m_isPaused = true;
}

void AnimatedSprite::stop()
{
	m_isPaused = true;
	m_currentFrame = 0;
	setFrame(m_currentFrame);
}


Animation AnimatedSprite::getAnimation() const
{
	return m_animation;
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
{
	sf::IntRect rect = m_animation.getFrame(m_currentFrame);

	float width = float(std::abs(rect.width));
	float height = float(std::abs(rect.height));

	return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

bool AnimatedSprite::isPlaying() const
{
	return !m_isPaused;
}

sf::Time AnimatedSprite::getFrameTime() const
{
	return m_frameTime;
}

void AnimatedSprite::setFrame(std::size_t newFrame, bool resetTime)
{
		sf::IntRect rect = m_animation.getFrame(newFrame);

		m_vertices[0].position = sf::Vector2f(0.f, 0.f);
		m_vertices[1].position = sf::Vector2f(0.f, float(rect.height));
		m_vertices[2].position = sf::Vector2f(float(rect.width), static_cast<float>(rect.height));
		m_vertices[3].position = sf::Vector2f(float(rect.width), 0.f);

		float left = float(rect.left) + 0.0001f;
		float right = left + float(rect.width);
		float top = float(rect.top);
		float bottom = top + float(rect.height);

		m_vertices[0].texCoords = sf::Vector2f(left, top);
		m_vertices[1].texCoords = sf::Vector2f(left, bottom);
		m_vertices[2].texCoords = sf::Vector2f(right, bottom);
		m_vertices[3].texCoords = sf::Vector2f(right, top);


	if (resetTime)
		m_currentTime = sf::Time::Zero;
}

void AnimatedSprite::update(sf::Time deltaTime)
{
	if (!m_isPaused)
	{
		m_currentTime += deltaTime;
		if (m_currentTime >= m_frameTime)
		{
			m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());
			if (m_currentFrame + 1 < m_animation.getSize()) m_currentFrame++;
			else m_currentFrame = 0;
			setFrame(m_currentFrame, false);
		}
	}
}

void AnimatedSprite::loadAnimation(int row)
{
	for (int i = 0; i < 4 ; i++)
	{
		m_animations[i].reset(new Animation);
		m_animations[i]->setTexture(m_texture);
		m_animations[i]->addFrame(sf::IntRect(3 * i*SIZE + 32,
			row*SIZE, 32, 32));
		m_animations[i]->addFrame(sf::IntRect(3 * i*SIZE + 64,
			row*SIZE, 32, 32));
		m_animations[i]->addFrame(sf::IntRect(3 * i*SIZE + 32,
			row*SIZE, 32, 32));
		m_animations[i]->addFrame(sf::IntRect(3 * i*SIZE + 0,
			row*SIZE, 32, 32));
	}
	
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//if (m_animation != NULL)
	//{
		states.transform *= getTransform();
		states.texture = &m_texture;
		target.draw(m_vertices, 4, sf::Quads, states);
	//}
}