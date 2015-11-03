#include "Element.h"

class Case : public Element
{
private:
	int occupation;
	int piege;
	int depart;
	
public:
	void setOccupation(int newOccupation);
	int getOccupation();

	void setPiege(int newPiege);
	int getPiege();

	void setDepart(int newDepart);
	int getDepart();
};