// AiPlayer.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 15:43
//
//
// This header file defines the interfaces to the class AiPlayer
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


#ifndef __AIPLAYER_H__
#define __AIPLAYER_H__


#include "../global.hpp"
#include "../boot/Bootstrap.hpp"
#include "../engine/AbstractEngine.hpp"
#include "../game/IGame.hpp"


namespace ai {

class AiPlayer: public game::IGame{
private:
private:
  AiBehavior  behavior;
public:
   AiPlayer(boot::Bootstrap* boot, engine::AbstractEngine* engine, int cid);
   ~AiPlayer();
  void  run();
  void  start();
  virtual void  syncRequest();
  virtual void  whoIsPlaying();
  virtual void  update(ObsType obs);
  virtual void  updateGlobal(state::Etat& e);
  virtual void  updateElement(state::Element& e1);
  virtual void  updateTurn(int turn);
  virtual void  updatePlayer(engine::Player pl);
  virtual void  updateGameEnd(int score);
  virtual void  updateNowPlaying(int pid);
  virtual void  canPlay(int pid);
  virtual void  hasPlayed(int pid);
  virtual void  sync(state::ElementList list);
  void  recherche1(state::ElementList* liste, int playerUid, engine::Character& c, engine::AbstractEngine* engine);

};

};

#endif // defined __AIPLAYER_H__
