#include "AnimationLayer.hpp"
#include "../test/game/TestGame.hpp"


AnimationLayer::AnimationLayer(Bootstrap* boot): Layer(boot), m_animation_running(false)
{
}

AnimationLayer::~AnimationLayer()
{
}


void AnimationLayer::updateAnims()
{
	m_animation_running = !(m_pending_moves.size() == 0);
	if (frameClock.getElapsedTime().asMilliseconds() <= 20) return;
	handleMoves();

	frameTime = frameClock.restart();

	for (auto sprite : m_sprites)
	{
		if (!m_animations_done[sprite.first]) {
			sprite.second->update(frameTime);

		}
	}
}

void AnimationLayer::update(const ElementList& list)
{
	int uid(0);
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i]->type == Mobile)
		{
			Perso* ptr = dynamic_cast<Perso*>(list[i].get());
			uid = ptr->getUid();
			std::map<int, AnimatedSprite*>::const_iterator it = m_sprites.find(uid);
			if (it == m_sprites.end())
			{
				// if not found, add it
				if (ptr->getUid() == 1) addSprite(TestGame::m_animated_sprite, ptr->getUid());
				else addSprite(TestGame::m_animated_sprite2, ptr->getUid());
				m_sprites[uid]->setPosition((OFFSET_X + list[i]->getX())*SIZE,
					(OFFSET_Y + list[i]->getY())*SIZE);
				m_sprites[uid]->setType(ptr->getDir());
				m_found_sprites[uid] = true;
			}
			else
			{
				m_found_sprites[uid] = true;
			}
		}
	}
	reflowSprites();
}

void AnimationLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::map<int, AnimatedSprite*>::const_iterator it;
	for (it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		target.draw(*it->second, states);
	}
}


void AnimationLayer::addSprite(AnimatedSprite& sprite, int id)
{
	m_sprites[id] = &sprite;
}

AnimatedSprite* AnimationLayer::getSprite(const int& uid)
{
	std::map<int, AnimatedSprite*>::const_iterator it = m_sprites.find(uid);
	if (it != m_sprites.end())
		return it->second;
	throw std::invalid_argument("Not found");
}

void AnimationLayer::addPendingMovement(int sprite_id, std::vector<Movement> moves)
{
	m_pending_moves[sprite_id] = moves;
}

const int AnimationLayer::getSpritesNumber()
{
	return m_sprites.size();
}

std::map<int, AnimatedSprite*> AnimationLayer::getSprites()
{
	return m_sprites;
}

bool AnimationLayer::isAnimationRunning()
{
	return m_animation_running;
}

void AnimationLayer::reflowSprites()
{
	std::vector<int> to_delete;
	for (auto sp : m_sprites)
	{

		LOG(DEBUG) << sp.first;
		if (m_found_sprites[sp.first]) continue;
		else to_delete.push_back(sp.first);
	}
	for (int i : to_delete) m_sprites.erase(i);
	m_found_sprites.clear();
}

void AnimationLayer::handleMoves()
{
	//LOG(DEBUG) << "Handling moves";
	if (m_pending_moves.size() == 0) return;
	for (auto it : m_pending_moves)
	{
		//LOG(DEBUG) << "Pending move " << it.first;
		if (it.second.size() != 0)
		{

			executeMoves(it.first);
			m_animations_done[it.first] = false;
		}
		if (it.second.size() == 0)
		{
			m_pending_moves.erase(it.first);
			m_animations_done[it.first] = true;
		}
		if (m_pending_moves.size() == 0) break;
	}
}

void AnimationLayer::executeMoves(int id)
{
	AnimatedSprite* sprite = m_sprites[id];
	Movement move = m_pending_moves[id].back();
	//LOG(DEBUG) << "Moving " << move.getDir();
	sprite->play(move.getDir());
	//sprite->setType(move.getDir());
	switch (move.getDir())
	{
	case MoveForward:
		sprite->move(0, -1 * SIZE / 8);
		break;
	case MoveBackward:
		sprite->move(0, 1 * SIZE / 8);
		break;
	case MoveLeft:
		sprite->move(-1 * SIZE / 8, 0);
		break;
	case MoveRight:
		sprite->move(1 * SIZE / 8, 0);
		break;
	}
	if (m_animations_progress[id] == 7) {
		m_pending_moves[id].pop_back();
		m_animations_progress[id] = 0;
	}
	else {
		m_animations_progress[id]++;
	}

}