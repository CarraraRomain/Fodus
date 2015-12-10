// ElementLayer.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class ElementLayer
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


#ifndef __ELEMENTLAYER_H__
#define __ELEMENTLAYER_H__


#include "../global.hpp"
#include "TileFactory.hpp"
#include "Layer.hpp"


namespace render {

class ElementLayer: public Layer{
private:
private:
  int  m_depth;
  std::unique_ptr<TileFactory>  m_tile_factory;
public:
   ElementLayer(boot::Bootstrap* boot, int depth);
   ~ElementLayer();
  virtual void  update(const state::ElementList& list);

};

};

#endif // defined __ELEMENTLAYER_H__
