#include "Scene.hpp"



Scene::Scene(Bootstrap* boot): m_boot(boot)
{
	LOG(DEBUG) << "Creating scene";
	ElementLayer* eltLayer = new ElementLayer(m_boot,0);
	ElementLayer* eltLayerUp = new ElementLayer(m_boot,1);
	eltLayerUp->clearVertices();
	m_layers.push_back(eltLayer);
	m_layers.push_back(eltLayerUp);
	m_elt_list = new LegacyElementList;
	LOG(DEBUG) << "Scene ready";
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

void Scene::update(const LegacyElementList& list)
{
	LOG(DEBUG) << "Updating scene";
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


void Scene::setEltAt(LegacyElement& elt, int x, int y, int depth)
{
	LegacyElement search_elt;
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
		LegacyElement elt = LegacyElement();
		elt.setKey(elt.getKey());
		elt.setX(x);
		elt.setY(y);
		elt.setD(depth);
		m_elt_list->push_back(elt);
	}

}