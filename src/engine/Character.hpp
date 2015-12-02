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
	void moveWatched();
	const bool hasMoved();
	void move(int perso);
	bool hasMoveWatch();
private:
	bool m_attacked;
	bool m_moved;
	bool m_move_watch;
	std::vector<Movement> m_movements;
};

