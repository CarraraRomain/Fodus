// TileFactory.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 02:02
//
//
// This header file defines the interfaces to the class TileFactory
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


#ifndef __TILEFACTORY_H__
#define __TILEFACTORY_H__


#include "../global.hpp"
#include "../boot/Bootstrap.hpp"
#include "Tile.hpp"


namespace render {

class TileFactory{
private:
private:
  boot::Bootstrap* m_boot;
public:
  std::shared_ptr<rapidjson::Document> _tilesDoc;

private:
  rapidjson::Value* getFactoryFor(std::string key);
public:
   TileFactory(boot::Bootstrap* boot);
   ~TileFactory();
  void  setTilesDoc(rapidjson::Document* doc);
  void  registerFacto(std::string key);
  Tile* buildTileForElt(std::string key);
  void  loadTilesDoc(const std::string& doc);
  std::shared_ptr<rapidjson::Document> getTilesDoc();

};

};

#endif // defined __TILEFACTORY_H__
