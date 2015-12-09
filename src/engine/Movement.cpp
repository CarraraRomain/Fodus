#include "Movement.hpp"

using namespace engine;

Movement::Movement()
{
}

Movement::Movement(int newx, int newy, AnimationType newtype)
{
	x = newx;
	y = newy;
	type = newtype;
}

Movement::~Movement()
{
}

const AnimationType Movement::getDir()
{
	return type;
}