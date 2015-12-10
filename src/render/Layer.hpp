// Layer.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 15:43
//
//
// This header file defines the interfaces to the class Layer
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


#ifndef __LAYER_H__
#define __LAYER_H__


#include "../global.hpp"
#include "../boot/Bootstrap.hpp"
#include "../state/ElementList.hpp"


namespace render {

class Layer: public sf::Drawable{
private:
protected:
  boot::Bootstrap* m_boot;
  sf::VertexArray  m_vertices;
  sf::Texture  m_tileset;
protected:
  virtual void  draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
   Layer(boot::Bootstrap* boot);
   ~Layer();
  bool  loadTileset(const std::string Tilesetpath);
  void  resetVertices();
  void  clearVertices();
  virtual void  update(const state::ElementList& list) = 0;

};

};

#endif // defined __LAYER_H__
