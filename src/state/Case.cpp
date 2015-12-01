#include "Case.h"

bool Case::isGround()
{
	return true;
}

bool Case::isAllie()
{
	return false;
}

bool Case::isEnnemy()
{
	return false;
}

bool Case::isNeutral()
{
	return false;
}

void Case::setAttribute(std::string attribute, int valeur)
{
	if (attribute == "occupation")occupation = valeur;
	if (attribute == "trap")trap = valeur;
	if (attribute == "start")start = valeur;
}

void Case::setAttribute(std::string attribute, std::string valeur)
{
}

int Case::getAttribute(std::string attribute)
{
	if (attribute == "occupation") return occupation;
	if (attribute == "trap") return trap;
	if (attribute == "start") return start;
}

Competence * Case::getSkill(int index)
{
	return NULL;
}

Classe Case::getType()
{
	return Sol;
}

Element* Case::clone()
{
	return new Case(*this);
}

Case::~Case()
{
}
