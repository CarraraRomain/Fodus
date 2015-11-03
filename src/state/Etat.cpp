#include "Etat.hpp"

void Etat::setTaille(int newTaille)
{
	taille = newTaille;
}

int Etat::getTaille()
{
	return taille;
}

std::vector<int> Etat::getEnnemies()
{
	int i;
	std::vector<int> result;

	for (i = 0; i < liste->size(); i++)
	{
		if ((*liste)[i]->isEnnemy()) {
			result.push_back(i);
		}
	}
	return result;
}

std::vector<int> Etat::getAllies()
{
	int i;
	std::vector<int> result;

	for (i = 0; i < liste->size(); i++)
	{
		if ((*liste)[i]->isAllie()) {
			result.push_back(i);
		}
	}
	return result;
}

std::vector<int> Etat::getNeutral()
{
	int i;
	std::vector<int> result;

	for (i = 0; i < liste->size(); i++)
	{
		if ((*liste)[i]->isNeutral()) {
			result.push_back(i);
		}
	}
	return result;
}

std::vector<int> Etat::getGround()
{
	int i;
	std::vector<int> result;

	for (i = 0; i < liste->size(); i++)
	{
		if ((*liste)[i]->isGround()) {
			result.push_back(i);
		}
	}
	return result;
}