// Character.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 02:02
//
//
// This header file defines the interfaces to the class Character
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


#ifndef __CHARACTER_H__
#define __CHARACTER_H__


#include "../global.hpp"
#include "Movement.hpp"


namespace engine {

class Character{
private:
private:
  bool  m_attacked;
  bool  m_moved;
  bool  m_move_watch;
  std::vector<Movement>  m_movements;
public:
  const int  UID;

public:
   Character(int id);
   Character();
   ~Character();
  void  addMove(Movement m);
  std::vector<Movement>& getMoves();
  void  resetMoves();
  void  resetAttacks();
  void  attack();
  void  moveWatched();
  const bool  hasMoved();
  const bool  hasAttacked();
  void  move();
  bool  hasMoveWatch();

};

};

#endif // defined __CHARACTER_H__
