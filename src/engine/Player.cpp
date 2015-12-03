#include "Player.hpp"



Player::Player(int id, int control): m_id(id), controlType(control)
{
	
}


Player::Player() {

}

Player::~Player()
{

}

const bool Player::hasMoved(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::hasMoved";
	return m_chars[perso]->hasMoved();
}

const bool Player::hasAttacked(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::hasAttacked";
	return m_chars[perso]->hasAttacked();
}

void Player::move(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::move";
	m_chars[perso]->move();
	//for(auto& ch:m_chars)
	

}

void Player::attack(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::attack";
	m_chars[perso]->attack();
}

void Player::resetMoves()
{
	for(auto const &it: m_chars)
	{
		m_moved[it.first] = false;
		m_chars[it.first]->resetMoves();
	}
}

// DEPRECATED
void Player::resetMove(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::resetMove";		
	m_moved[perso] = false;
//	m_chars[perso]->resetMoves();
}

// DEPRECATED
void Player::resetAttack(int perso)
{
	LOG(WARNING) << "Deprecated Call : Player::resetAttack";
	m_chars[perso]->resetAttacks();
}

void Player::resetAttacks()
{
	for (auto const &it : m_chars)
	{
		m_attacked[it.first] = false;
		m_chars[it.first]->resetAttacks();
	}
	
}

std::map<int, bool>::iterator Player::getMovedBegin()
{
	return m_moved.begin();
}

std::map<int, bool>::iterator Player::getMovedEnd()
{
	return m_moved.end();
}

const int Player::getId()
{
	return m_id;
}


void Player::addOwnedPerso(int elt)
{
	m_chars[elt].reset(new Character(elt));
}


const Character& Player::operator[](size_t i)
{
	return *(m_chars[i]);
}


int Player::numberPersos() const
{
	return m_chars.size();
}

void Player::addMove(int perso, int x, int y, AnimationType type)
{
	m_chars[perso]->addMove(Movement(x, y, type));
}

std::vector<Movement>& Player::getMove(int perso)
{
	return m_chars[perso]->getMoves();
}

bool Player::isHuman()
{
	return (controlType == 0);
}

void Player::removePerso(int uid)
{
	m_chars.erase(uid);
}

Player &Player::operator=(const Player &player) {
	m_id = player.m_id;
	m_moved.clear();
	m_moved = player.m_moved;
	controlType = player.controlType;
	m_chars.clear();
	for(auto const &ch: player.m_chars){
		m_chars[ch.first].reset(new Character(*ch.second));
	}
	return *this;
}

Player &Player::operator=(Player &&player) {
	m_id = player.m_id;
	m_moved.clear();
	m_moved = player.m_moved;
	controlType = player.controlType;
	m_chars.clear();
	for(auto const & ch: player.m_chars){
		m_chars[ch.first].reset(new Character(*ch.second));
	}
	return *this;
}

int Player::size() const
{
	return m_chars.size();
}

Player::Player(const Player &player) {
	m_id = player.m_id;
	m_moved.clear();
	m_moved = player.m_moved;
	controlType = player.controlType;
	m_chars.clear();
	for(auto const & ch: player.m_chars){
		m_chars[ch.first].reset(new Character(*ch.second));
	}
}

Player::iterator Player::begin() {
	return m_chars.begin();
}

Player::iterator Player::end() {
	return m_chars.end();
}

Player::const_iterator Player::begin() const {
	return m_chars.begin();
}

Player::const_iterator Player::cbegin() const {
	return m_chars.cbegin();
}

Player::const_iterator Player::cend() const {
	return m_chars.cend();
}

Player::const_iterator Player::end() const {
	return m_chars.end();
}
