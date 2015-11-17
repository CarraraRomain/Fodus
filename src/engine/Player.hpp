#pragma once
#include <vector>
#include "../Enum.h"
#include "Movement.hpp"

class Player
{
public:
	Player(int);
	Player();
	~Player();
	const bool hasMoved();
	const bool hasAttacked();
	void moved();
	void attacked();
	void resetMoved();
	void resetAttacked();
	const int getId();
	void addMovement(int x, int y, AnimationType type);
private:
	int m_id;
	bool m_moved;
	bool m_attacked;
	std::vector<Movement> movements;
};

