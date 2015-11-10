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
	int limiteZombie;
	int niveau;
	int seuil;

	std::vector<Competence> competences;
	Classe type;

public:
	virtual bool isAllie() override;
	virtual bool isEnnemy() override;
	virtual bool isNeutral() override;
	virtual bool isGround() override;

	virtual void setAttribute(std::string attribute, int valeur) override;
	virtual void setAttribute(std::string attribute, std::string valeur) override;
	virtual int getAttribute(std::string attribute) override;
};