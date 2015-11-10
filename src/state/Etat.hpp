#include "ElementList.hpp"
#include <vector>
#include <string>

#ifndef __Etat__
#define __Etat__

class Etat
{
private:
	int taille;
	ElementList liste;

public:
	void setTaille(int newTaille);
	int getTaille();
	void setAttribute(std::string attribute, int valeur, int uid);
	void setAttribute(std::string attribute, std::string valeur, int uid);

	std::vector<int> getEnnemies();
	std::vector<int> getAllies();
	std::vector<int> getNeutral();
	std::vector<int> getGround();

	int getSize();

	ElementList getList();
};
#endif