#pragma once

#include "ElementLayer.hpp"
#include "InfoLayer.hpp"
#include "AnimatedSprite.hpp"
#include "../engine/Movement.hpp"
#include "AnimationLayer.hpp"


class Scene :
	public sf::Drawable,
	public Subject
{
public:
	Scene(Bootstrap*);
	~Scene();	
	virtual void notify() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const ElementList& list);
	void update();
	void updateAnims();
	Element* getEltAt(int x, int y, int depth=0);
	void setEltAt(Element& elt, int x, int y, int depth = 0);
	void addPendingMovement(int sprite_id, std::vector<Movement> moves);
	bool isAnimationRunning();
	bool isAnimationRunning(int);
	AnimationLayer* getAnims() const;
	InfoLayer* getInfos() const;
	int getAnimsLeft(int sprite_id);
private:
	Bootstrap* m_boot;
	std::vector<Layer*> m_layers;
	AnimationLayer* m_anims;
	InfoLayer* m_infos;
	ElementList m_elt_list;

};

