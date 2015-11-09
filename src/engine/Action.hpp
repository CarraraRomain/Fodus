#include "../state/Etat.hpp"

class Action
{
public:
	virtual void apply(Etat e) = 0;
};