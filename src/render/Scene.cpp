#include "Scene.hpp"



Scene::Scene(std::string EltResJSON)
{
	ElementLayer* eltLayer = new ElementLayer(0, EltResJSON);
	ElementLayer* eltLayerUp = new ElementLayer(1, EltResJSON);
	eltLayerUp->clearVertices();
	m_layers.push_back(eltLayer);
	m_layers.push_back(eltLayerUp);
}


Scene::~Scene()
{
	for (Layer* layer : m_layers) delete layer;
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(Layer* layer: m_layers)
	{
		target.draw(*layer, states);
	}
}

void Scene::update(ElementList* list)
{
	for (Layer* layer : m_layers)
	{
		(*layer).update(list);
	}
}