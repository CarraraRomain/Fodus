#pragma once
#include <vector>
#include "../Enum.h"
#include "Movement.hpp"

#include "../state/perso.hpp"

class Player
{
public:
	Player(int, int);
	Player();
	~Player();
	const bool hasMoved(int);
	const bool hasAttacked(int);
	void move(int perso);
	void attack(int perso);
	void resetMoves();
	void resetMove(int perso);
	void resetAttack(int perso);
	void resetAttacks();
	std::map<int,bool>::iterator getMovedBegin();
	std::map<int, bool>::iterator getMovedEnd();

	const int getId();
	std::vector<Movement>& getMoves();
	void addOwnedPerso(int elt);
	int& operator[](size_t i);
	const int& operator[](size_t i) const;
	int numberPersos() const;
	void addMove(int perso, int x, int y, AnimationType type);
	std::vector<Movement>& getMove(int perso);
	bool isHuman();
	void removePerso(int uid);

private:
	int m_id;
	std::map<int, bool> m_moved;
	std::map<int, bool> m_attacked;
	std::vector<int> m_owned_persos;
	//std::vector<Movement> movements;
	std::map<int, std::vector<Movement>> m_movements;

	int controlType;
};
