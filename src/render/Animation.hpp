// Animation.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 15:43
//
//
// This header file defines the interfaces to the class Animation
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


#ifndef __ANIMATION_H__
#define __ANIMATION_H__


#include "../global.hpp"


namespace render {

class Animation{
private:
private:
  const sf::Texture* m_texture;
  std::vector<sf::IntRect> m_frames;
public:
   Animation();
   ~Animation();
  void  addFrame(sf::IntRect rect);
  void  setTexture(const sf::Texture& texture);
  const sf::Texture* getTexture() const;
  std::size_t  getSize() const;
  const sf::IntRect& getFrame(std::size_t i) const;

};

};

#endif // defined __ANIMATION_H__
