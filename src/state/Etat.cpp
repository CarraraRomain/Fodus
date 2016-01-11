#include "Etat.hpp"
#include "../engine/Observer.hpp"

using namespace state;

Etat::Etat(int i): turnsCount(i), taille(0), gameEnded(false), m_score(0)
{
}

Etat::~Etat()
{
}

void Etat::setTaille(int newTaille)
{
	taille = newTaille;
}

int Etat::getTaille()
{
	return taille;
}

void Etat::setAttribute(std::string attribute, int valeur, int uid)
{
	liste.setAttribute(attribute, valeur, uid);
}

void Etat::setAttribute(std::string attribute, std::string valeur, int uid)
{
	liste.setAttribute(attribute, valeur, uid);
}

int Etat::getAttribute(std::string attribute, int uid)
{
	return liste.getAttribute(attribute, uid);
}

const int Etat::getTurn()
{
	return turnsCount;
}

void Etat::nextTurn()
{
	turnsCount++;
}

std::vector<int> Etat::getEnnemies()
{
	int i;
	std::vector<int> result;

	for (i = 0; i < liste.size(); i++)
	{
		if (liste[i]->isEnnemy()) {
			result.push_back(i);
		}
	}
	return result;
}

std::vector<int> Etat::getAllies()
{
	int i;
	std::vector<int> result;

	for (i = 0; i < liste.size(); i++)
	{
		if (liste[i]->isAllie()) {
			result.push_back(i);
		}
	}
	return result;
}

std::vector<int> Etat::getNeutral()
{
	int i;
	std::vector<int> result;

	for (i = 0; i < liste.size(); i++)
	{
		if (liste[i]->isNeutral()) {
			result.push_back(i);
		}
	}
	return result;
}

std::vector<int> Etat::getGround()
{
	int i;
	std::vector<int> result;

	for (i = 0; i < liste.size(); i++)
	{
		if (liste[i]->isGround()) {
			result.push_back(i);
		}
	}
	return result;
}

void Etat::notify()
{
	for (engine::Observer* obs : m_obs)
	{
		obs->update(ObsState);
	}

}

int Etat::getSize()
{
	return liste.size();
}

void Etat::setResult(int score)
{
	gameEnded = true;
	m_score = score;
}

bool Etat::hasWin()
{
	return (m_score >0);
}

bool Etat::hasEnded()
{
	return gameEnded;
}

ElementList* Etat::getList()
{
	return &liste;
}


Etat::Etat(): turnsCount(0), taille(0)
{

}
