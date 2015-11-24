#pragma once
class Coord
{
public:
	Coord(int x, int y);
	~Coord();
	const int x;
	const int y;
	bool isAttackable();
	bool canMoveTo();
	void setNotAttackable();
	void setAttackable();
	void setCanMoveTo();
	void setCannotMoveTo();
	int move_weight;
	int attack_weight;
private:
	bool move;
	bool attackable;
		
};

