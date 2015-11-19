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
			Perso* ptr = dynamic_cast<Perso*>(list[i].get());
			uid = ptr->getUid();
			std::map<int, AnimatedSprite*>::const_iterator it = m_sprites.find(uid);
			if (it == m_sprites.end())
			{
				// if not found, add it
				if(ptr->getUid()== 1) addSprite(TestGame::m_animated_sprite, ptr->getUid());
				else addSprite(TestGame::m_animated_sprite2, ptr->getUid());
				m_sprites[uid]->setPosition((OFFSET_X + list[i]->getX())*SIZE,
					(OFFSET_Y + list[i]->getY())*SIZE);
				m_sprites[uid]->setType(ptr->getDir());
			}else
			{
				//handleMoves();
				it->second->setPosition((OFFSET_X +list[i]->getX())*SIZE,
					(OFFSET_Y + list[i]->getY())*SIZE);
				it->second->setType(ptr->getDir());
				
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

void Scene::updateAnims()
{
	frameTime = frameClock.restart();
	for (auto sprite:m_sprites)
	{
		sprite.second->update(frameTime);
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

void Scene::addSprite(AnimatedSprite& sprite, int id)
{
	m_sprites[id] = &sprite;
}

AnimatedSprite* Scene::getSprite(const int& uid)
{
	std::map<int, AnimatedSprite*>::const_iterator it = m_sprites.find(uid);
	if (it != m_sprites.end())
		return it->second;
	throw std::invalid_argument("Not found");
}

void Scene::addPendingMovement(int sprite_id, std::vector<Movement> moves)
{
	m_pending_moves[sprite_id] = moves;
}

const int Scene::getSpritesNumber()
{
	return m_sprites.size();
}

std::map<int, AnimatedSprite*> Scene::getSprites()
{
	return m_sprites;
}

void Scene::handleMoves()
{
	LOG(DEBUG) << "Handling moves";
	std::cout << m_pending_moves.size();
		if (m_pending_moves.size() == 0) return ;
	for (auto it: m_pending_moves)
	{
		LOG(DEBUG) << "Pending move " << it.first;
		if (it.second.size() != 0) executeMoves(it.first);
		if (it.second.size() == 0) m_pending_moves.erase(it.first);
		if (m_pending_moves.size() == 0) break;
	}
}

void Scene::executeMoves(int id)
{
	AnimatedSprite* sprite = m_sprites[id];
	Movement move = m_pending_moves[id].back();
	LOG(DEBUG) << "Moving " << move.getDir();
	switch (move.getDir())
		{
		case MoveForward:
			sprite->move(0, 1*SIZE*frameTime.asSeconds());
		break;
		case MoveBackward:
			sprite->move(0, -1 * SIZE*frameTime.asSeconds());
		break;
		case MoveLeft:
			sprite->move(-1 * SIZE*frameTime.asSeconds(), 0);
		break;
		case MoveRight:
			sprite->move(1 * SIZE*frameTime.asSeconds(), 0);
		break;
		}
	sprite->play(move.getDir());
	m_pending_moves[id].pop_back();
}