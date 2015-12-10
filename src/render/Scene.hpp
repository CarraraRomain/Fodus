// Scene.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class Scene
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


#ifndef __SCENE_H__
#define __SCENE_H__


#include "../global.hpp"
#include "../engine/Subject.hpp"
#include "../engine/Movement.hpp"
#include "Layer.hpp"
#include "ElementLayer.hpp"
#include "InfoLayer.hpp"
#include "AnimationLayer.hpp"


namespace render {

class Scene: public sf::Drawable, public engine::Subject{
private:
private:
  boot::Bootstrap* m_boot;
  AnimationLayer* m_anims;
  InfoLayer* m_infos;
  state::ElementList  m_elt_list;
  std::vector<Layer*>  m_layers;
public:
   Scene(boot::Bootstrap* boot);
   ~Scene();
  virtual void  notify();
  void  draw(sf::RenderTarget& target, sf::RenderStates states) const;
  void  update(const state::ElementList& list);
  void  update();
  void  updateAnims();
  state::Element* getEltAt(int x, int y, int depth);
  void  setEltAt(state::Element& elt, int x, int y, int depth);
  void  addPendingMovement(int sprite_id, std::vector<engine::Movement> moves);
  bool  isAnimationRunning();
  bool  isAnimationRunning(int i);
  void  hideMoveMap();
  void  showMoveMap();
  AnimationLayer* getAnims() const;
  InfoLayer* getInfos() const;
  int  getAnimsLeft(int sprite_id);

};

};

#endif // defined __SCENE_H__
