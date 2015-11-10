#include "../state/Etat.hpp"

class Action
{
public:
	virtual void execute(Etat e) = 0;
};