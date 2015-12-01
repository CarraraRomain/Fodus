#include "Element.h"

class Case : public Element
{
private:
	int occupation;
	int trap;
	int start;
	
public:
	virtual bool isGround() override;
	virtual bool isAllie() override;
	virtual bool isEnnemy() override;
	virtual bool isNeutral() override;

	virtual void setAttribute(std::string attribute, int valeur) override;
	virtual void setAttribute(std::string attribute, std::string valeur) override;
	virtual int getAttribute(std::string attribute);
	virtual Competence* getSkill(int index) override;
	virtual Classe getType() override;
	Case(int id): Element(id, Fixed) {}
	virtual Element* clone() override;
	~Case();
};