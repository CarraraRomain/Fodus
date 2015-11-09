#include "Move.hpp"

void Move::apply(Etat e)
{
	e.setAttribute("posX", posX, uid);
	e.setAttribute("posY", posY, uid);
}
