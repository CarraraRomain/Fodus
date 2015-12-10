// EngineObserver.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 02:02
//
//
// This header file defines the interfaces to the class EngineObserver
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


#ifndef __ENGINEOBSERVER_H__
#define __ENGINEOBSERVER_H__


#include "../global.hpp"
#include "AbstractEngine.hpp"


namespace engine {

class EngineObserver{
private:
private:
  AbstractEngine* m_engine;
public:
  int  CID;

protected:
  AbstractEngine* getEngine();
public:
   EngineObserver(AbstractEngine* engine, int cid);
   ~EngineObserver();
  virtual void  update(ObsType obs) = 0;
  virtual void  updateGlobal(state::Etat& e) = 0;
  virtual void  updateElement(state::Element& el) = 0;
  virtual void  updateTurn(int turn) = 0;
  virtual void  updatePlayer(Player pl) = 0;
  virtual void  updateGameEnd(int turn) = 0;
  virtual void  updateNowPlaying(int pid) = 0;
  virtual void  canPlay(int pid) = 0;
  virtual void  hasPlayed(int pid) = 0;
  virtual void  sync(state::ElementList list) = 0;

};

};

#endif // defined __ENGINEOBSERVER_H__
