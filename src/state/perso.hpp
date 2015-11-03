#include "Element.h"
#include "Competence.hpp"
#include <vector>

class Perso : public Element
{
private:

	enum Classe {
		Principal,
		Zombie,
		Monstre,
		Guerrier,
		Mage
	};

	std::string nom;
	int sante;
	int defense;
	int puissance;
	int deplacement;
	int corruption;
	int status;
	int portee;
	int santeCourante;
	int limitZombi;
	int niveau;
	int seuil;

	std::vector<Competence> competences;
	Classe type;

public:
	void setNom(std::string newNom);
	std::string getNom();

	void setSante(int newSante);
	int getSante();

	void setDefense(int newDefense);
	int getDefense();

	void setPuissance(int newPuissance);
	int getPuissance();

	void setDeplacement(int newDeplacement);
	int getDeplacement();

	void setCorruption(int newCorruption);
	int getCorruption();

	void setStatus(int newStatus);
	int getStatus();

	void setPortee(int newPortee);
	int getPortee();

	void setSanteCourante(int newSanteCourante);
	int getSanteCourante();

	void setLimitZombi(int newLimitZombi);
	int getLimitZombi();

	void setNiveau(int newNiveau);
	int getNiveau();

	void setSeuil(int newSeuil);
	int getSeuil();

	virtual bool isAllie() override;
	virtual bool isEnnemy() override;
	virtual bool isNeutral() override;
};