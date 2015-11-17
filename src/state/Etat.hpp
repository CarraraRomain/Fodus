#ifndef __Etat__
#define __Etat__

#include "ElementList.hpp"
#include <vector>
#include <string>


#include "../engine/Subject.hpp"
#include "../engine/Observer.hpp"

class Etat: public Subject
{
private:
	int taille;
	ElementList liste;
	int turnsCount;

public:
	explicit Etat(int);
	~Etat();
	void setTaille(int newTaille);
	int getTaille();
	void setAttribute(std::string attribute, int valeur, int uid);
	void setAttribute(std::string attribute, std::string valeur, int uid);
	int getAttribute(std::string attribute, int uid);
	const int getTurn();
	void nextTurn();
	std::vector<int> getEnnemies();
	std::vector<int> getAllies();
	std::vector<int> getNeutral();
	std::vector<int> getGround();
	void notify() override;
	int getSize();

	ElementList* getList();
};
#endif