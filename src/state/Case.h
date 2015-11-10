#include "Element.h"

class Case : public Element
{
private:
	int occupation;
	int piege;
	int depart;
	
public:
	virtual bool isGround() override;
	virtual bool isAllie() override;
	virtual bool isEnnemy() override;
	virtual bool isNeutral() override;

	virtual void setAttribute(std::string attribute, int valeur) override;
	virtual void setAttribute(std::string attribute, std::string valeur) override;
	virtual int getAttribute(std::string attribute);
};