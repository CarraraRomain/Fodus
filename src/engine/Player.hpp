#pragma once
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
private:
	int m_id;
	bool m_moved;
	bool m_attacked;
};

