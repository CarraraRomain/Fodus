#include "perso.hpp"

Perso::~Perso()
{
}

bool Perso::isAllie()
{
	if (type == Principal || type == Zombie) return true;
	else return false;
}

bool Perso::isEnnemy()
{
	if (type == Guerrier || type == Mage) return true;
	else return false;
}

bool Perso::isNeutral()
{
	if (type == Monstre) return true;
	else return false;
}

bool Perso::isGround()
{
	return false;
}

AnimationType Perso::getDir()
{
	return direction;
}

const int Perso::getOwner() const
{
	return owner;
}

const Classe Perso::getClass() const
{
	return type;
}

void Perso::setClass(Classe c)
{
	type = c;
}

void Perso::setAttribute(std::string attribute, int valeur)
{
	if (attribute == "health") health = valeur;
	if (attribute == "defence") defence = valeur;
	if (attribute == "power") power = valeur;
	if (attribute == "move") move = valeur;
	if (attribute == "corruption") corruption = valeur;
	if (attribute == "status") status = valeur;
	if (attribute == "range") range = valeur;
	if (attribute == "currentHealth") currentHealth = valeur;
	if (attribute == "zombiLimit") zombiLimit = valeur;
	if (attribute == "level") level = valeur;
	if (attribute == "conversion") conversion = valeur;
	if (attribute == "posX") m_x = valeur;
	if (attribute == "posY") m_y = valeur;
	if (attribute == "owner") owner = valeur;
}

void Perso::setAttribute(std::string attribute, std::string valeur)
{
	if (attribute == "name")nom = valeur;
	if (attribute == "direction") {
		if (valeur == "Forward") direction = MoveForward;
		else if (valeur == "Backward") direction = MoveBackward;
		else if (valeur == "Left") direction = MoveLeft;
		else if (valeur == "Right") direction = MoveRight;
	}
}

int Perso::getAttribute(std::string attribute)
{
	if (attribute == "health") return health;
	if (attribute == "defence") return defence;
	if (attribute == "power") return power;
	if (attribute == "move") return move;
	if (attribute == "corruption") return corruption;
	if (attribute == "status") return status;
	if (attribute == "range") return range;
	if (attribute == "currentHealth") return currentHealth;
	if (attribute == "zombiLimit") return zombiLimit;
	if (attribute == "level") return level;
	if (attribute == "conversion") return conversion;
	if (attribute == "posX") return m_x;
	if (attribute == "posY") return m_y;
	if (attribute == "uid") return uid;
	if (attribute == "owner") return owner;
}
