// Ruler.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-09 22:14
//
//
// This header file defines the interfaces to the class Ruler
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


#ifndef __RULER_H__
#define __RULER_H__


#include "../global.hpp"
#include "../state/Etat.hpp"
#include "../engine/Command.hpp"
#include "ActionList.hpp"
#include "DeadAction.hpp"
#include "RestoreAction.hpp"
#include "EndGameAction.hpp"
#include "StatusAction.hpp"
#include "PoisonAction.hpp"
#include "SpawnAction.hpp"
#include "DamageAction.hpp"
#include "MoveAction.hpp"
#include "MoveCommand.hpp"
#include "SkillCommand.hpp"


namespace engine {

class Engine;

class Ruler{
private:
private:
  state::Etat& m_state;
  std::unique_ptr<ActionList>  m_action_list;
  bool  m_end;
  engine::Engine* m_engine;
  std::vector< std::vector<int> > map;
  std::map<int, std::vector< std::vector<int> > > mapCharacter;
public:
   Ruler(engine::Engine* e, state::Etat& state);
   ~Ruler();
  void  execute(engine::Command* com, state::Etat* state);
  void  update();
  bool  checkMove(state::Etat* state, int x, int y, int uid, int player);
  bool  createMove(state::Etat* state, int x, int y, int uid, int player);
  bool  checkAttack(state::Etat* state, int uid1, int uid2, int player);
  bool  createAttack(state::Etat* state, int uid1, int uid2);
  int  checkSkill(state::Etat* state, int posX, int posY, int uid, int skillIndex, int player);
  bool  createSkill(state::Etat* state, int uid, int index, int posX, int posY, int target);
  void  createMap(state::Etat* state);
  void  createMapCharacter(int uid);
  void  propagate(int posX, int posY, int value, int uid);
  void  nextPlayer(int played, int toPlay, state::Etat* state);
  int  getMapValue(int x, int y, int uid);
  void  checkRule(state::Etat* state);
  void  EndTurnRule(int played, state::Etat* state);

};

};

#endif // defined __RULER_H__
