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
	if (attribute == "piege")piege = valeur;
	if (attribute == "depart")depart = valeur;
}

void Case::setAttribute(std::string attribute, std::string valeur)
{
}

int Case::getAttribute(std::string attribute)
{
	if (attribute == "occupation") return occupation;
	if (attribute == "piege") return piege;
	if (attribute == "depart") return depart;
}