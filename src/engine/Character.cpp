#include "Character.hpp"



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

void Character::moveWatched()
{
	m_move_watch = true;
}

const bool Character::hasMoved()
{
	return m_moved;
}

void Character::move(int perso)
{
	m_moved = true;
}

bool Character::hasMoveWatch()
{
	return m_move_watch;
}

Character::Character(): UID(0) {

}
