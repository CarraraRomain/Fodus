#include "../state/Etat.hpp"
//#include "CommandeListe.hpp"
#include "Ruler.hpp"
#include "AbstractEngine.hpp"

class Engine: public AbstractEngine
{
public:
	Engine();
	void handleCommand(Command*) override;
	void run();
	Etat& getState() override;
	int registerPlayer(int client, int player) override;
	int connect(int client) override;

protected:
	int registerPlayer(int player) override;

private :
	std::unique_ptr<Etat> state;
	//CommandeListe liste;
	std::vector<int> m_has_played;
	std::unique_ptr<Ruler> m_ruler;
};