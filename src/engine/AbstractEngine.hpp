// AbstractEngine.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class AbstractEngine
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


#ifndef __ABSTRACTENGINE_H__
#define __ABSTRACTENGINE_H__


#include "../global.hpp"
#include "../state/Etat.hpp"
#include "Player.hpp"
#include "CommandReceiver.hpp"


namespace engine {

class EngineObserver;

class AbstractEngine: public CommandReceiver{
private:
protected:
  std::vector<int>  m_clients;
  int  m_player_playing;
  int  current_player_uid;
  std::map<int, EngineObserver*> m_players_obs;
  std::map<int, Player> m_players;
public:
  std::map<int, int> m_clients_players;

protected:
  virtual int  registerPlayer(int player) = 0;
  virtual void  notifyGlobal();
  virtual void  notifySingle(int pid);
  virtual void  notifyElement(state::Element& el);
  virtual void  notifyTurn(int turn);
  virtual void  notifyNowPlaying(int pid);
  virtual void  notifyCanPlay(int pid);
  virtual void  notifyPlayer(Player pl);
  virtual void  notifyHasPlayed(int pid);
public:
   AbstractEngine();
   ~AbstractEngine();
  virtual state::Etat& getState() = 0;
  virtual int  registerPlayer(int player, EngineObserver* obs) = 0;
  virtual int  connect(int client) = 0;
  virtual void  start() = 0;
  virtual void  run() = 0;
  virtual state::ElementList  syncRequest() = 0;
  virtual void  syncFull(int pid) = 0;
  virtual int  whoIsPlaying() = 0;
  virtual std::vector< std::vector<int> > getMap(int uid) = 0;
  virtual std::map<int, Player>& getPlayers() = 0;
  virtual Player& getPlayer(int ) = 0;
  virtual void  propagate(int x, int y, int valeur, int uid) = 0;
  virtual int  getMapValue(int x, int y, int uid) = 0;
  virtual void  notifyGameEnd(Player pl, int score);

};

};

#endif // defined __ABSTRACTENGINE_H__
