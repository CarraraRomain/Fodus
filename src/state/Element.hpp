
#ifndef __Base_h__
#define __Base_h__

#include <string>
#include "../global.hpp"
#include "Competence.hpp"
class Element
{
public:
	void setX(int newX);
	int getX();

	void setY(int newY);
	int getY();

	void setD(int newD);
	int getD();

	int getUid();

	void setKey(std::string key);
	std::string getKey();
	const ElementType type;
	virtual bool isGround() = 0;
	virtual bool isAllie() = 0;
	virtual bool isNeutral() = 0;
	virtual bool isEnnemy() = 0;
	
	virtual void setAttribute(std::string attribute, int valeur) = 0;
	virtual void setAttribute(std::string attribute, std::string valeur) = 0;
	virtual int getAttribute(std::string) = 0;
	virtual Competence* getSkill(int index) = 0;
	virtual Classe getType() = 0;
	Element(int id, ElementType type): type(type), uid(id) {}
	virtual Element* clone() = 0;
protected:
	std::string m_key;
	
	int m_x;
	int m_y;
	int m_d;
	int uid;
};

#endif