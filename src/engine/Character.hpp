#pragma once
#include "../global.hpp"
#include "Movement.hpp"

class Character
{
public:
	Character(int id);
	Character();
	~Character();
	const int UID;
	void addMove(Movement m);
	std::vector<Movement>& getMoves();
	void resetMoves();
	void resetAttacks();
	void attack();
private:
	bool m_attacked;
	bool m_moved;
	std::vector<Movement> m_movements;
};

