// Tile.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class Tile
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


#ifndef __TILE_H__
#define __TILE_H__


#include "../global.hpp"


namespace render {

class Tile{
private:
private:
  int  _id;
  std::string  _key;
  int  _x;
  int  _y;
  int  _width;
  int  _height;
  int  _tileNumber;
public:
   Tile(const rapidjson::Value& key);
   ~Tile();
  int  getId() const;
  void  setId(int id);
  const std::string & getKey() const;
  void  setKey(const std::string& key);
  int  getX() const;
  void  setX(int x);
  int  getY() const;
  void  setY(int y);
  int  getWidth() const;
  void  setWidth(int width);
  int  getHeight() const;
  void  setHeight(int height);
  int  getTileNumber() const;
  void  setTileNumber(int tileNumber);

};

};

#endif // defined __TILE_H__
