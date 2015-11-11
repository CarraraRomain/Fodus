#include "../state/Etat.hpp"
//#include "CommandeListe.hpp"
#include "Ruler.hpp"

class Engine: public CommandReceiver
{
public:
	Engine();
	void handleCommand(Command*) override;
	void run();
	Etat& getState();

private :
	std::unique_ptr<Etat> state;
	//CommandeListe liste;
	std::unique_ptr<Ruler> m_ruler;
};