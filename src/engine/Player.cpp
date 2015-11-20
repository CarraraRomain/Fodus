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
	return m_moved[perso];
}

const bool Player::hasAttacked(int perso)
{
	return m_attacked[perso];
}

void Player::move(int perso)
{
	m_moved[perso] = true;
}

void Player::attack(int perso)
{
	m_attacked[perso] = true;
}

void Player::resetMoves()
{
	for(auto it: m_moved)
	{
		m_moved[it.first] = false;
		m_movements[it.first].clear();
	}
}

void Player::resetMove(int perso)
{
	m_moved[perso] = false;
	m_movements[perso].resize(0);
}

void Player::resetAttack(int perso)
{
	m_attacked[perso] = false;
}

void Player::resetAttacks()
{
	for (auto it : m_attacked)
	{
		it.second = false;
	}
	
}

const int Player::getId()
{
	return m_id;
}


void Player::addOwnedPerso(int elt)
{
	m_owned_persos.push_back(elt);
}

int& Player::operator[](size_t i)
{
	return m_owned_persos[i];
}

const int& Player::operator[](size_t i) const
{
	return m_owned_persos[i];
}

int Player::numberPersos() const
{
	return m_owned_persos.size();
}

void Player::addMove(int perso, int x, int y, AnimationType type)
{
	m_movements[perso].push_back(Movement(x, y, type));
}

std::vector<Movement>& Player::getMove(int perso)
{
	return m_movements[perso];
}

bool Player::isHuman()
{
	if (controlType == 0)return true;
	else return false;
}
