#pragma once

#include "ElementLayer.hpp"

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
	

private:
	Bootstrap* m_boot;
	std::vector<Layer*> m_layers;
	LegacyElementList* m_elt_list;

};

