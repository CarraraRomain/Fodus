#include "perso.hpp"

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

void Perso::setAttribute(std::string attribute, int valeur)
{
	if (attribute == "health") health = valeur;
	if (attribute == "defence") defence = valeur;
	if (attribute == "power") power = valeur;
	if (attribute == "movement") movement = valeur;
	if (attribute == "corruption") corruption = valeur;
	if (attribute == "status") status = valeur;
	if (attribute == "scope") scope = valeur;
	if (attribute == "currentHealth") currentHealth = valeur;
	if (attribute == "limitZombie") limitZombie = valeur;
	if (attribute == "level") level = valeur;
	if (attribute == "seuil") seuil = valeur;
	if (attribute == "posX") m_x = valeur;
	if (attribute == "posY") m_y = valeur;
}

void Perso::setAttribute(std::string attribute, std::string valeur)
{
	if (attribute == "nom")nom = valeur;
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
	if (attribute == "movement") return movement;
	if (attribute == "corruption") return corruption;
	if (attribute == "status") return status;
	if (attribute == "scope") return scope;
	if (attribute == "currentHealth") return currentHealth;
	if (attribute == "limitZombie") return limitZombie;
	if (attribute == "level") return level;
	if (attribute == "seuil") return seuil;
	if (attribute == "posX") return m_x;
	if (attribute == "posY") return m_y;
	if (attribute == "uid") return uid;
}
