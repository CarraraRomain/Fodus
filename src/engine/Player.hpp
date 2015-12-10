// Player.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 02:02
//
//
// This header file defines the interfaces to the class Player
//
// This file was generate from a Dia Diagram using pydia2code.py
// by Timothe Perez <achille.ash@gmail.com>
// based on the work of Dave Klotzbach <dklotzbach@foxvalley.net>
//
// The author asserts no additional copyrights on the derived product. Limitations
// on the uses of this file are the right and responsibility of authors of the source
// diagram.
//
// The pydia2code.py and dia-uml2cpp.xsl script are distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// A copy of the GNU General Public License is available by writing to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
// MA 02111-1307, USA.
//


#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "../global.hpp"
#include "Character.hpp"


namespace engine {

class Player{
private:
private:
  int  m_id;
  int  controlType;
  std::map<int, std::unique_ptr<Character> > m_chars;
  std::map<int, bool> m_moved;
  std::map<int, bool> m_attacked;
public:
  int  side;
  typedef std::map<int, std::unique_ptr<Character>>::iterator iterator;
  typedef std::map<int, std::unique_ptr<Character>>::const_iterator const_iterator;

public:
   Player(int , int );
   Player();
   Player(const Player& );
   ~Player();
  const int  getId();
  bool  isHuman();
  int  size() const;
  iterator  begin();
  iterator  end();
  const_iterator  begin() const;
  const_iterator  cbegin() const;
  const_iterator  end() const;
  const_iterator  cend() const;
  void  addOwnedPerso(int elt);
  void  removePerso(int uid);
  int  numberPersos() const;
  const bool  hasMoved(int );
  void  move(int perso);
  void  addMove(int perso, int x, int y, AnimationType type);
  std::vector<Movement>& getMove(int perso);
  void  resetMoves();
  void  resetMove(int perso);
  void  attack(int perso);
  const bool  hasAttacked(int );
  void  resetAttack(int perso);
  void  resetAttacks();
  Player& operator=(Player& );
  Player& operator=(Player&& ) const;
  Character& operator[](size_t i);
  std::map<int, bool>::iterator getMoveBegin();
  std::map<int, bool>::iterator getMoveEnd();

};

};

#endif // defined __PLAYER_H__
