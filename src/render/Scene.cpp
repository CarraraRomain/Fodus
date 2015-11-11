#include "Scene.hpp"
#include "../state/Case.h"
#include "../test/game/TestGame.hpp"


Scene::Scene(Bootstrap* boot): m_boot(boot)
{
	LOG(DEBUG) << "Creating scene";
	ElementLayer* eltLayer = new ElementLayer(m_boot,0);
	ElementLayer* eltLayerUp = new ElementLayer(m_boot,1);
	eltLayerUp->clearVertices();
	m_layers.push_back(eltLayer);
	m_layers.push_back(eltLayerUp);
	m_elt_list = new ElementList;
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
	std::map<int, AnimatedSprite*>::const_iterator it;
	for (it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		it->second->play(MoveForward);
		target.draw(*it->second, states);
	}
}

void Scene::update(const ElementList& list)
{
	LOG(DEBUG) << "Updating scene";
	int uid(42);
	// saving EltList is disabled for now
	//*m_elt_list = *list;
	for (Layer* layer : m_layers)
	{
		layer->update(list);
	}
	for (int i = 0; i < list.size();i++)
	{
		if (list[i]->type == Mobile)
		{
			std::map<int, AnimatedSprite*>::const_iterator it = m_sprites.find(uid);
			if (it == m_sprites.end())
			{
				addSprite(TestGame::m_animated_sprite);
				m_sprites[uid]->setPosition(list[i]->getX()*SIZE,
					list[i]->getY()*SIZE);
			}else
			{
				it->second->setPosition(list[i]->getX()*SIZE,
					list[i]->getY()*SIZE);
				
			}

		

		}
	}
}

void Scene::update()
{
	for (Layer* layer : m_layers)
	{
		layer->update(*m_elt_list);
	}
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

void Scene::addSprite(AnimatedSprite& sprite)
{
	m_sprites[42] = &sprite;
}

const AnimatedSprite& Scene::getSprite(const int& uid)
{
	std::map<int, AnimatedSprite*>::const_iterator it = m_sprites.find(uid);
	if (it != m_sprites.end())
		return *(it->second);
	throw std::invalid_argument("Not found");
}