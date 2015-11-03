#include "Case.h"

void Case::setOccupation(int newOccupation)
{
	occupation = newOccupation;
}

int Case::getOccupation()
{
	return occupation;
}

void Case::setPiege(int newPiege)
{
	piege = newPiege;
}

int Case::getPiege()
{
	return piege;
}

void Case::setDepart(int newDepart)
{
	depart = newDepart;
}

int Case::getDepart()
{
	return depart;
}

bool Case::isGround()
{
	return true;
}
