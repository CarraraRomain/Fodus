// InfoLayer.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 02:02
//
//
// This header file defines the interfaces to the class InfoLayer
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


#ifndef __INFOLAYER_H__
#define __INFOLAYER_H__


#include "../global.hpp"
#include "../engine/Observer.hpp"
#include "../state/Perso.hpp"
#include "Coord.hpp"
#include "Layer.hpp"


namespace render {

class InfoLayer: public Layer, public engine::Observer{
private:
private:
  sf::Font  m_font;
  sf::Vector2i  m_player;
  int  move_qty;
  bool  m_disable_actions;
  bool  m_show_map;
public:
  std::map<int, sf::Text> m_perso_texts;
  std::map<int, bool> m_display_texts;
  std::vector<std::vector<int>> m_map;
  std::vector<Coord*> m_coords;

public:
   InfoLayer(boot::Bootstrap* boot, engine::Subject* sub);
   ~InfoLayer();
  virtual void  update(ObsType obs);
  virtual void  update(const state::ElementList& list);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  void  updateVertices();
  void  setPlayer(int x, int y);
  int  relax(int x, int y, int vx, int vy);
  void  ford(int x, int y);
  void  disable();
  void  enable();
  void  hideMoveMap();
  void  showMoveMap();
  void  syncMoveMap();
  void  syncMoveMap(std::vector<std::vector<int>>& map);
  void  resetMoveMap();

};

};

#endif // defined __INFOLAYER_H__
