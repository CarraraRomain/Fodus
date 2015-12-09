#include "Coord.hpp"

using namespace game;

Coord::Coord(int x, int y): x(x), y(y), move(true), attackable(false)
{
}

Coord::~Coord()
{
}

bool Coord::isAttackable()
{
	return attackable;
}

bool Coord::canMoveTo()
{
	return move;
}

void Coord::setNotAttackable()
{
	attackable = false;
}

void Coord::setAttackable()
{
	attackable = true;
}

void Coord::setCanMoveTo()
{
	move = true;
}

void Coord::setCannotMoveTo()
{
	move = false;
}