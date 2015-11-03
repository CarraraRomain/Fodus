#include "Competence.hpp"

void Competence::setNom(std::string newNom)
{
	nom = newNom;
}

std::string Competence::getNom()
{
	return nom;
}

void Competence::setDegats(int newDegats)
{
	degats = newDegats;
}

int Competence::getDegats()
{
	return degats;
}

void Competence::setZone(int newZone)
{
	zone = newZone;
}

int Competence::getZone()
{
	return zone;
}

void Competence::setInteret(int newInteret)
{
	interet = newInteret;
}

int Competence::getInteret()
{
	return interet;
}

void Competence::setCible(int newCible)
{
	cible = newCible;
}

int Competence::getCible()
{
	return cible;
}
