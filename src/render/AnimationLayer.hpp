#pragma once
#include "Layer.hpp"
#include "../engine/Movement.hpp"
#include "AnimatedSprite.hpp"

class AnimationLayer :
	public Layer
{
public:
	AnimationLayer(Bootstrap* boot);
	~AnimationLayer();
	void updateAnims();
	
	virtual void update(const ElementList& list) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void addSprite(AnimatedSprite& sprite, int id);
	AnimatedSprite* getSprite(const int& uid);
	void addPendingMovement(int sprite_id, std::vector<Movement> moves);
	const int getSpritesNumber();
	std::map<int, AnimatedSprite*> getSprites();
	std::map<int, AnimatedSprite*> m_sprites;
	std::map<int, bool> m_found_sprites;
	bool isAnimationRunning();
	bool isAnimationRunning(int id);
	void reflowSprites();

private:
	sf::Time frameTime;
	sf::Clock frameClock;
	float speed = 80.f;
	std::map<int, std::vector<Movement>> m_pending_moves;
	bool m_animation_running;
	std::map<int, bool> m_animations_done;
	std::map<int, int> m_animations_progress;
	void handleMoves();
	void executeMoves(int id);
	void executeMove(int id, int i);
};

