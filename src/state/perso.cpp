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
	if (attribute == "defense") defense = valeur;
	if (attribute == "puissance") puissance = valeur;
	if (attribute == "deplacement") deplacement = valeur;
	if (attribute == "corruption") corruption = valeur;
	if (attribute == "status") status = valeur;
	if (attribute == "portee") portee = valeur;
	if (attribute == "santeCourante") santeCourante = valeur;
	if (attribute == "limiteZombie") limiteZombie = valeur;
	if (attribute == "niveau") niveau = valeur;
	if (attribute == "seuil") seuil = valeur;
	if (attribute == "posX") m_x = valeur;
	if (attribute == "posY") m_y = valeur;
}

void Perso::setAttribute(std::string attribute, std::string valeur)
{
	if (attribute == "nom")nom = valeur;
}

int Perso::getAttribute(std::string attribute)
{
	if (attribute == "sante") return sante;
	if (attribute == "defense") return defense;
	if (attribute == "puissance") return puissance;
	if (attribute == "deplacement") return deplacement;
	if (attribute == "corruption") return corruption;
	if (attribute == "status") return status;
	if (attribute == "portee") return portee;
	if (attribute == "santeCourante") return santeCourante;
	if (attribute == "limiteZombie") return limiteZombie;
	if (attribute == "niveau") return niveau;
	if (attribute == "seuil") return seuil;
	if (attribute == "posX") return m_x;
	if (attribute == "posY") return m_y;
}
