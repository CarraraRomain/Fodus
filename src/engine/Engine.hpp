// Engine.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class Engine
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


#ifndef __ENGINE_H__
#define __ENGINE_H__


#include "../global.hpp"
#include "../boot/Bootstrap.hpp"
#include "../state/Etat.hpp"
#include "../state/Perso.hpp"
#include "../state/Competence.hpp"
#include "Ruler.hpp"
#include "AbstractEngine.hpp"


namespace engine {

class Engine: public AbstractEngine{
private:
public:
  virtual ~Engine();
private:
  boot::Bootstrap* m_boot;
  std::unique_ptr<state::Etat>  state;
  std::vector<int>  m_has_played;
  std::unique_ptr<Ruler>  m_ruler;
private:
  void  nextPlayer(int played);
  void  nextTurn();
protected:
  int  registerPlayer(int player);
public:
   Engine(boot::Bootstrap* boot);
  void  loadLevel(std::string );
  void  handleCommand(Command* );
  void  run();
  int  getCurrentPlayer();
  bool  hasPlayed(int player);
  state::Etat& getState();
  int  registerPlayer(int player, EngineObserver* obs);
  int  connect(int client);
  void  start();
  Player& getPlayer(int );
  std::map<int, Player>& getPlayers();
  int  getMapValue(int x, int y, int uid);
  std::vector< std::vector<int> > getMap(int uid);
  void  death(int uid);
  void  propagate(int x, int y, int valeur, int uid);
  state::ElementList  syncRequest();
  void  syncFull(int );
  int  whoIsPlaying();

};

};

#endif // defined __ENGINE_H__
