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
	AnimationType direction;

	std::vector<Competence> competences;
	Classe type = Principal;

public:
	Perso(int id) : Element(id, Mobile), sante(100), defense(100), puissance(100),
		deplacement(2), corruption(10), status(1), portee(5),
		santeCourante(100), limiteZombie(300), niveau(1), seuil(42),
		direction(MoveForward)
	{}
	~Perso();
	virtual bool isAllie() override;
	virtual bool isEnnemy() override;
	virtual bool isNeutral() override;
	virtual bool isGround() override;
	AnimationType getDir();
	virtual void setAttribute(std::string attribute, int valeur) override;
	virtual void setAttribute(std::string attribute, std::string valeur) override;
	virtual int getAttribute(std::string attribute) override;
};