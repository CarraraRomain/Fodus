#pragma once
#include <vector>
#include "../Enum.h"
#include "Movement.hpp"

#include "../state/perso.hpp"
#include "Character.hpp"

class Player
{
public:
	typedef std::map<int, std::unique_ptr<Character>>::iterator iterator;
	typedef std::map<int, std::unique_ptr<Character>>::const_iterator const_iterator;

	Player(int, int);
	Player();
	Player(const Player&);
	~Player();

	int side;
	const int getId();
	bool isHuman();

	Player& operator=(const Player&);
	Player&operator=(Player&&);
	int size() const;
	Character& operator[](size_t i);
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator cbegin() const;
	const_iterator end() const ;
	const_iterator cend() const ;
	//////////////////////////
	// PERSOS
	void addOwnedPerso(int elt);
	void removePerso(int uid);
	int numberPersos() const;
	/////////////////////////
	// MOVES
	const bool hasMoved(int);
	void move(int perso);
	void addMove(int perso, int x, int y, AnimationType type);
	std::vector<Movement>& getMove(int perso);
	std::map<int, bool>::iterator getMovedBegin();
	std::map<int, bool>::iterator getMovedEnd();
	//std::vector<Movement>& getMoves();
	void resetMoves();
	void resetMove(int perso);
	/////////////////////////
	// ATTACKS
	void attack(int perso);
	const bool hasAttacked(int);
	void resetAttack(int perso);
	void resetAttacks();

private:
	int m_id;
	std::map<int, bool> m_moved;
	std::map<int, bool> m_attacked;
	//std::vector<int> m_owned_persos;
	//std::vector<Movement> movements;
	//std::map<int, std::vector<Movement>> m_movements;
	std::map<int, std::unique_ptr<Character> > m_chars;
	int controlType;
};
