#include <string>

class Competence
{
private:
	std::string nom;
	int degats;
	int zone;
	int interet;
	int cible;

public:
	void setNom(std::string newNom);
	std::string getNom();

	void setDegats(int newDegats);
	int getDegats();

	void setZone(int newZone);
	int getZone();

	void setInteret(int newInteret);
	int getInteret();

	void setCible(int newCible);
	int getCible();

};