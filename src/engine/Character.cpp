#include "Character.hpp"



Character::Character(int id) : UID(id), m_attacked(false), m_moved(false)
{
}


Character::~Character()
{
}

void Character::addMove(Movement m)
{
	m_movements.push_back(m);
}

std::vector<Movement>& Character::getMoves()
{
	return m_movements;
}

void Character::resetMoves()
{
	m_moved = false;
	m_movements.resize(0);
}

void Character::resetAttacks()
{
	m_attacked = false;
}

Character::Character(): UID(0) {

}
