#pragma once

#include "ElementLayer.hpp"

class Scene :
	public sf::Drawable
{
public:
	Scene(Bootstrap*);
	~Scene();	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const ElementList& list);
	void update();
	Element* getEltAt(int x, int y, int depth=0);
	void setEltAt(Element& elt, int x, int y, int depth = 0);
	

private:
	Bootstrap* m_boot;
	std::vector<Layer*> m_layers;
	ElementList* m_elt_list;

};

