#include "ElementList.hpp"
#include <vector>

class Etat
{
private:
	int taille;
	std::unique_ptr<ElementList> liste;

public:
	void setTaille(int newTaille);
	int getTaille();

	std::vector<int> getEnnemies();
	std::vector<int> getAllies();
	std::vector<int> getNeutral();
	std::vector<int> getGround();
};