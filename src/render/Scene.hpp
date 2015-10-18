#pragma once

#include "ElementLayer.hpp"

class Scene :
	public sf::Drawable
{
public:
	Scene(std::string EltResJSON);
	~Scene();	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(ElementList* list);
private:
	std::vector<Layer*> m_layers;

};

