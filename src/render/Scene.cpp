#include "Scene.hpp"
#include "../state/Case.h"
#include "../test/game/TestGame.hpp"


Scene::Scene(Bootstrap* boot): m_boot(boot)
{
	LOG(DEBUG) << "Creating scene";
	ElementLayer* eltLayer = new ElementLayer(m_boot,0);
	ElementLayer* eltLayerUp = new ElementLayer(m_boot,1);
	eltLayerUp->clearVertices();
	AnimationLayer* animLayer = new AnimationLayer(m_boot);
	InfoLayer* infoLayer = new InfoLayer(m_boot, this);
	m_layers.push_back(eltLayer);
	m_layers.push_back(eltLayerUp);
	m_layers.push_back(animLayer);
	m_layers.push_back(infoLayer);
	
	m_anims = animLayer;
	m_infos = infoLayer;
	attach(infoLayer);
	m_elt_list = new ElementList;
	
	LOG(DEBUG) << "Scene ready";
}


Scene::~Scene()
{
	for (Layer* layer : m_layers) delete layer;
	
	delete m_elt_list;
}

void Scene::notify()
{
	for (auto obs : m_obs)
	{
		obs->update(ObsAnimation);
	}
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
	LOG(DEBUG) << "Updating scene";
	// saving EltList is disabled for now
	//*m_elt_list = *list;
	for (Layer* layer : m_layers)
	{
		layer->update(list);
	}
	

}

void Scene::update()
{
	for (Layer* layer : m_layers)
	{
		layer->update(*m_elt_list);
	}
}

void Scene::updateAnims()
{
	m_anims->updateAnims();
	notify();
}

void Scene::setEltAt(Element& elt, int x, int y, int depth)
{
	bool found = false;
	for (int i = 0; i < int(m_elt_list->size()); i++)
	{

		if ((*m_elt_list)[i]->getX() == x && 
			(*m_elt_list)[i]->getY() == y &&
			(*m_elt_list)[i]->getD() == depth)
		{
			(*m_elt_list)[i]->setKey(elt.getKey());
			found = true;
			break;
		}
	}
	if(!found)
	{
		if(elt.type == Fixed)
		{
			Case* ptr_case = new Case(rand());
			ptr_case->setKey(elt.getKey());
			ptr_case->setX(x);
			ptr_case->setY(y);
			ptr_case->setD(depth);
			m_elt_list->push_back(ptr_case);
		}
		
	}

}

void Scene::addPendingMovement(int sprite_id, std::vector<Movement> moves)
{
	m_anims->addPendingMovement(sprite_id, moves);
}

bool Scene::isAnimationRunning()
{
	return m_anims->isAnimationRunning();
}

AnimationLayer* Scene::getAnims() const
{
	return m_anims;
}

InfoLayer* Scene::getInfos() const
{
	return m_infos;
}