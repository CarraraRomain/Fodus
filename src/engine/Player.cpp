#include "Player.hpp"



Player::Player(int id): m_id(id)
{
	m_attacked = false;
	m_moved = false;
}

Player::Player()
{
	m_attacked = false;
	m_moved = false;
}

Player::~Player()
{
}

const bool Player::hasMoved()
{
	return m_moved;
}

const bool Player::hasAttacked()
{
	return m_attacked;
}

void Player::moved()
{
	m_moved = true;
}

void Player::attacked()
{
	m_attacked = true;
}

void Player::resetMoved()
{
	m_moved = false;
}

void Player::resetAttacked()
{
	m_attacked = false;
}

const int Player::getId()
{
	return m_id;
}

void Player::addMovement(int x, int y, AnimationType type)
{
	movements.push_back(Movement(x, y, type));
}
