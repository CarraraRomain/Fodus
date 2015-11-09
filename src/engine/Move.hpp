#include "Action.hpp"
#include <string>

class Move : public Action
{
private:
	int uid;
	int posX;
	int posY;

public:
	virtual void apply(Etat e) override;
};