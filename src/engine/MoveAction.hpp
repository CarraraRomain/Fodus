// MoveAction.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 15:43
//
//
// This header file defines the interfaces to the class MoveAction
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


#ifndef __MOVEACTION_H__
#define __MOVEACTION_H__


#include "../global.hpp"
#include "Action.hpp"


namespace engine {

class MoveAction: public Action{
private:
private:
  int  uid;
  int  posX;
  int  posY;
  AnimationType  dir;
public:
  virtual void  execute(state::Etat& e);
   MoveAction(int uid, int posX, int posY, AnimationType type);
   ~MoveAction();

};

};

#endif // defined __MOVEACTION_H__
