#include "Scene.hpp"



Scene::Scene(std::string EltResJSON)
{
	ElementLayer* eltLayer = new ElementLayer(EltResJSON);
	m_layers.push_back(eltLayer);
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