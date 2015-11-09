#include "../state/Etat.hpp"
//#include "CommandeListe.hpp"
#include "Ruler.hpp"

class Engine
{
public :
	void run();

private :
	Etat state;
	//CommandeListe liste;
	Ruler rule;
};