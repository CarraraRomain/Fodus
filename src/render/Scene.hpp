#pragma once

#include "ElementLayer.hpp"
#include "AnimatedSprite.hpp"

class Scene :
	public sf::Drawable
{
public:
	Scene(Bootstrap*);
	~Scene();	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const LegacyElementList& list);
	void update();
	LegacyElement* getEltAt(int x, int y, int depth=0);
	void setEltAt(LegacyElement& elt, int x, int y, int depth = 0);
	void addSprite(AnimatedSprite& sprite);
	const AnimatedSprite& getSprite(const int& uid);
private:
	Bootstrap* m_boot;
	std::vector<Layer*> m_layers;
	std::map<int, AnimatedSprite*> m_sprites;
	LegacyElementList* m_elt_list;

};

