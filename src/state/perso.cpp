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

void Perso::setAttribute(std::string attribute, int valeur)
{
	if (attribute == "sante") sante = valeur;
	if (attribute == "defense") sante = valeur;
	if (attribute == "puissance") sante = valeur;
	if (attribute == "deplacement") sante = valeur;
	if (attribute == "corruption") sante = valeur;
	if (attribute == "status") sante = valeur;
	if (attribute == "portee") sante = valeur;
	if (attribute == "santeCourante") sante = valeur;
	if (attribute == "limiteZombie") sante = valeur;
	if (attribute == "niveau") sante = valeur;
	if (attribute == "seuil") sante = valeur;
	if (attribute == "posX") m_x = valeur;
	if (attribute == "posY") m_y = valeur;
}

void Perso::setAttribute(std::string attribute, std::string valeur)
{
	if (attribute == "nom")nom = valeur;
}
