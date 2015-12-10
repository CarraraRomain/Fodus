// AnimationLayer.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class AnimationLayer
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


#ifndef __ANIMATIONLAYER_H__
#define __ANIMATIONLAYER_H__


#include "../global.hpp"
#include "../state/Perso.hpp"
#include "../engine/Movement.hpp"
#include "SpriteFactory.hpp"
#include "Layer.hpp"


namespace render {

class AnimationLayer: public Layer{
private:
private:
  SpriteFactory  m_factory;
  sf::Time  frameTime;
  sf::Clock  frameClock;
  bool  m_animation_running;
  std::map<int, int> m_animations_progress;
  std::map<int, bool>  m_animations_done;
  std::map<int, std::vector<engine::Movement>>  m_pending_moves;
public:
  std::map<int, AnimatedSprite*> m_sprites;
  std::map<int, bool> m_found_sprites;

private:
  void  handleMoves();
  void  executeMoves(int id);
  void  executeMove(int id, int i);
public:
   AnimationLayer(boot::Bootstrap* boot);
   ~AnimationLayer();
  void  updateAnims();
  virtual void  update(const state::ElementList& list);
  virtual void  draw(sf::RenderTarget& target, sf::RenderStates states) const;
  void  addSprite(AnimatedSprite& sprite, int id);
  void  addPendingMovement(int sprite_id, std::vector<engine::Movement> moves);
  const int  getSpritesNumber();
  bool  isAnimationRunning();
  bool  isAnimationRunning(int id);
  void  reflowSprites();
  std::map<int, AnimatedSprite*> getSprites();
  AnimatedSprite* getSprite(const int& uid);

};

};

#endif // defined __ANIMATIONLAYER_H__
