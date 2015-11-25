#pragma once
#include "Element.h"
#include "Competence.hpp"
#include "../global.hpp"

class Perso : public Element
{
private:

	
	std::string nom;
	int side;
	int health;
	int defence;
	int power;
	int move;
	int corruption;
	int status;
	int range;
	int currentHealth;
	int zombiLimit;
	int level;
	int conversion;
	AnimationType direction;
	int owner;
	std::vector<Competence> competences;
	Classe type = Principal;

public:
	Perso(int id, int player) : Element(id, Mobile), side(0), health(100), defence(100), power(100),
		move(2), corruption(10), status(1), range(5),
		currentHealth(100), zombiLimit(300), level(1), conversion(42),
		direction(MoveForward), owner(player)
	{}
	~Perso();
	virtual bool isAllie() override;
	virtual bool isEnnemy() override;
	virtual bool isNeutral() override;
	virtual bool isGround() override;
	AnimationType getDir();
	const int getOwner() const; 
	const Classe getClass() const;
	void setClass(Classe);
	virtual void setAttribute(std::string attribute, int valeur) override;
	virtual void setAttribute(std::string attribute, std::string valeur) override;
	virtual int getAttribute(std::string attribute) override;
};