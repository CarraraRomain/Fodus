#include "Movement.hpp"



Movement::Movement(int newx, int newy, AnimationType newtype)
{
	x = newx;
	y = newy;
	type = newtype;
}

Movement::~Movement()
{
}
