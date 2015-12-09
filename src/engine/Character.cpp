#include "Character.hpp"

using namespace engine;

Character::Character(int id) : UID(id), m_move_watch(false), m_attacked(false), m_moved(false)
{
}


Character::~Character()
{
}

void Character::addMove(Movement m)
{
	m_movements.push_back(m);
	m_moved = true;
}

std::vector<Movement>& Character::getMoves()
{
	return m_movements;
}

void Character::resetMoves()
{
	m_moved = false;
	m_move_watch = false;
	m_movements.resize(0);
}

void Character::resetAttacks()
{
	m_attacked = false;
}

void Character::attack()
{
	m_attacked = true;
}

void Character::moveWatched()
{
	m_move_watch = true;
}

const bool Character::hasMoved()
{
	return m_moved;
}

const bool Character::hasAttacked()
{
	return m_attacked;
}

void Character::move()
{
	m_moved = true;
}

bool Character::hasMoveWatch()
{
	return m_move_watch;
}

Character::Character(): UID(0) {

}
