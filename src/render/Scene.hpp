#pragma once

#include "ElementLayer.hpp"
#include "AnimatedSprite.hpp"
#include "../engine/Movement.hpp"

class Scene :
	public sf::Drawable
{
public:
	Scene(Bootstrap*);
	~Scene();	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const ElementList& list);
	void update();
	void updateAnims();
	Element* getEltAt(int x, int y, int depth=0);
	void setEltAt(Element& elt, int x, int y, int depth = 0);
	void addSprite(AnimatedSprite& sprite, int id);
	AnimatedSprite* getSprite(const int& uid);
	void addPendingMovement(int sprite_id, std::vector<Movement> moves);
	const int getSpritesNumber();
	std::map<int, AnimatedSprite*> getSprites();
	std::map<int, AnimatedSprite*> m_sprites;
	bool isAnimationRunning();
private:
	sf::Time frameTime;
	sf::Clock frameClock;
	float speed = 80.f;
	Bootstrap* m_boot;
	std::vector<Layer*> m_layers;
	
	std::map<int, std::vector<Movement>> m_pending_moves;
	bool m_animation_running;
	std::map<int, bool> m_animations_done;
	std::map<int, int> m_animations_progress;
	ElementList* m_elt_list;
	void handleMoves();
	void executeMoves(int id);
	void executeMove(int id, int i);

};

