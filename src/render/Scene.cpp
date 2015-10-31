#include "Scene.hpp"



Scene::Scene(std::string EltResJSON)
{

	ElementLayer* eltLayer = new ElementLayer(0, EltResJSON);
	ElementLayer* eltLayerUp = new ElementLayer(1, EltResJSON);
	eltLayerUp->clearVertices();
	m_layers.push_back(eltLayer);
	m_layers.push_back(eltLayerUp);
	m_elt_list = new ElementList;
}


Scene::~Scene()
{
	for (Layer* layer : m_layers) delete layer;
	delete m_elt_list;
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(Layer* layer: m_layers)
	{
		target.draw(*layer, states);
	}
}

void Scene::update(const ElementList& list)
{
	// saving EltList is disabled for now
	//*m_elt_list = *list;
	for (Layer* layer : m_layers)
	{
		(*layer).update(list);
	}
}

void Scene::update()
{
	for (Layer* layer : m_layers)
	{
		(*layer).update(*m_elt_list);
	}
}


void Scene::setEltAt(Element& elt, int x, int y, int depth)
{
	Element search_elt;
	bool found = false;
	for (int i = 0; i < int(m_elt_list->size()); i++)
	{
		search_elt = *(*m_elt_list)[i];
		if (search_elt.getX() == x && search_elt.getY() == y && search_elt.getD() == depth)
		{
			search_elt.setKey(elt.getKey());
			found = true;
			break;
		}
	}
	if(!found)
	{
		Element elt = Element();
		elt.setKey(elt.getKey());
		elt.setX(x);
		elt.setY(y);
		elt.setD(depth);
		m_elt_list->push_back(elt);
	}

}