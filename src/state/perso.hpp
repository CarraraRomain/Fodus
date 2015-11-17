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
	int health;
	int defence;
	int power;
	int movement;
	int corruption;
	int status;
	int scope;
	int currentHealth;
	int limitZombie;
	int level;
	int seuil;
	AnimationType direction;

	std::vector<Competence> competences;
	Classe type = Principal;

public:
	Perso(int id) : Element(id, Mobile), health(100), defence(5), power(10),
		movement(2), corruption(10), status(1), scope(5),
		currentHealth(100), limitZombie(300), level(1), seuil(42),
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