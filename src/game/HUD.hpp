// HUD.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-09 22:14
//
//
// This header file defines the interfaces to the class HUD
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


#ifndef __HUD_H__
#define __HUD_H__


#include "../global.hpp"


namespace game {

class HUD{
private:
private:
  boot::Bootstrap* m_boot;
  sf::Vector2u  m_window_size;
  sf::Font  m_font;
  sf::Texture  m_dashboard_texture;
  sf::RectangleShape  m_dashboard;
  int  m_turns;
  bool  m_disable_action;
private:
  void  setFont(std::string key);
public:
   HUD(boot::Bootstrap* boot);
   ~HUD();
  void  draw(sf::RenderTarget& target, sf::RenderStates states);
  void  load(sf::Vector2u window_size);
  void  updateTurns(int turn);
  void  updateMoveCapa(bool b);
  void  updateAttackCapa(bool b);
  void  turnFinished();
  void  newTurn();
  void  actionsDisabled();
  void  actionsEnabled();
  void  updateAction(int skillMode);

};

};

#endif // defined __HUD_H__
