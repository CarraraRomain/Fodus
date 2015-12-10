// AnimatedSprite.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 15:43
//
//
// This header file defines the interfaces to the class AnimatedSprite
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


#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__


#include "../global.hpp"
#include "Animation.hpp"


namespace render {

class AnimatedSprite: public sf::Drawable, public sf::Transformable{
private:
private:
  bool  init;
  Animation  m_animation;
  AnimationType  m_type;
  sf::Time  m_frameTime;
  sf::Time  m_currentTime;
  std::size_t  m_currentFrame;
  sf::Texture  m_texture;
  bool  m_isPaused;
public:
  std::unique_ptr<Animation> m_animations[4];
  sf::Vertex m_vertices[4];

private:
  virtual void  draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
   ~AnimatedSprite();
   AnimatedSprite(sf::Time frameTime, bool paused, int row);
  void  update(sf::Time deltaTime);
  void  setAnimation(int i);
  void  setType(AnimationType type);
  void  loadAnimation(int row);
  void  setFrameTime(sf::Time time);
  void  play();
  void  play(AnimationType type);
  void  pause();
  void  stop();
  Animation  getAnimation() const;
  sf::FloatRect  getLocalBounds() const;
  sf::FloatRect  getGlobalBounds() const;
  bool  isPlaying() const;
  sf::Time  getFrameTime() const;
  void  setFrame(std::size_t newFrame, bool resetTime = true);

};

};

#endif // defined __ANIMATEDSPRITE_H__
