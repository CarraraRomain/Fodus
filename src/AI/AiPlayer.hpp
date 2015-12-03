#include "../global.hpp"
#include "../game/IGame.hpp"
#include "../engine/EndTurnCommand.hpp"
#include "../engine/MoveCommand.h"
#include "../engine/AttackCommand.h"
#include "../engine/Character.hpp"

class AiPlayer : public IGame
{
public:
	AiPlayer(Bootstrap* boot, AbstractEngine* engine, int cid);
	~AiPlayer();

	void run();
	void start();
	virtual void syncRequest() override;
	virtual void whoIsPlaying() override;

	virtual void update(ObsType) override;
	virtual void updateGlobal(Etat& e) override;
	virtual void updateElement(Element& e1) override;
	virtual void updateTurn(int turn) override;
	virtual void updatePlayer(Player pl) override;
	virtual void updateGameEnd(int score) override;
	virtual void updateNowPlaying(int pid) override;
	virtual void canPlay(int pid) override;
	virtual void hasPlayed(int pid) override;
	virtual void sync(ElementList list) override;

	void recherche1(ElementList* liste, int playerUid, Character& c, AbstractEngine* engine);

private:
	AiBehavior behavior;
};
