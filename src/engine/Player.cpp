#include "Player.hpp"



Player::Player(int id, int control): m_id(id), controlType(control)
{
	
}

Player::Player()
{

}
Player::~Player()
{

}

const bool Player::hasMoved(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::hasMoved";
	return m_moved[perso];
}

const bool Player::hasAttacked(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::hasAttacked";
	return m_attacked[perso];
}

void Player::move(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::move";
	m_moved[perso] = true;
}

void Player::attack(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::attack";
	m_attacked[perso] = true;
}

void Player::resetMoves()
{
	//for(auto const &it: m_chars)
	{
		//m_moved[it.first] = false;
		//m_chars[it.first]->resetMoves();
	}
}

// DEPRECATED
void Player::resetMove(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::resetMove";		
	m_moved[perso] = false;
	m_chars[perso]->resetMoves();
}

// DEPRECATED
void Player::resetAttack(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::resetAttack";
	m_attacked[perso] = false;
}

void Player::resetAttacks()
{
	for (auto it : m_moved)
	{
		m_attacked[it.first] = false;
	}
	
}

std::map<int, bool>::iterator Player::getMovedBegin()
{
	return m_moved.begin();
}

std::map<int, bool>::iterator Player::getMovedEnd()
{
	return m_moved.end();
}

const int Player::getId()
{
	return m_id;
}


void Player::addOwnedPerso(int elt)
{
	std::unique_ptr<Character> ptr(new Character(elt));
	m_chars[elt] = std::move(ptr);
}

const Character& Player::operator[](size_t i)
{
	return *(m_chars[i]);
}

int Player::numberPersos() const
{
	return m_chars.size();
}

void Player::addMove(int perso, int x, int y, AnimationType type)
{
	m_chars[perso]->addMove(Movement(x, y, type));
}

std::vector<Movement>& Player::getMove(int perso)
{
	return m_chars[perso]->getMoves();
}

bool Player::isHuman()
{
	return (controlType == 0);
}

void Player::removePerso(int uid)
{
	m_chars.erase(uid);

}
