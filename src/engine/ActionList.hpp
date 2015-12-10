// ActionList.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class ActionList
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


#ifndef __ACTIONLIST_H__
#define __ACTIONLIST_H__


#include "../global.hpp"
#include "Action.hpp"


namespace engine {

class ActionList{
private:
public:
  std::vector<std::unique_ptr<Action>> m_actions;

public:
   ActionList();
   ~ActionList();
   ActionList(const ActionList& );
   ActionList(ActionList&& );
  size_t  size() const;
  void  push_back(Action* );
  void  clear();
  void  remove(int i);
  std::unique_ptr<Action>& operator[](size_t i);
  const std::unique_ptr<Action>& operator[](size_t i) const;
  ActionList& operator=(const ActionList& );
  ActionList& operator=(ActionList&& );

};

};

#endif // defined __ACTIONLIST_H__
