#include "Action.hpp"
#include <string>
#include "../Enum.h"

class MoveAction : public Action
{
private:
	int uid;
	int posX;
	int posY;

public:
	virtual void execute(Etat& e) override;
	MoveAction(int uid, int posX, int posY);
	virtual ~MoveAction();
};