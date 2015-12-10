// Element.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class Element
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


#ifndef __ELEMENT_H__
#define __ELEMENT_H__


#include "../global.hpp"
#include "Competence.hpp"


namespace state {

class Element{
private:
public:
  virtual ~Element();
protected:
  std::string  m_key;
  int  m_x;
  int  m_y;
  int  m_d;
  int  uid;
  Classe classe;
public:
  ElementType  type;

public:
  void  setX(int newX);
  int  getX();
  void  setY(int newY);
  int  getY();
  void  setD(int newD);
  int  getD();
  int  getUid();
  void  setKey(std::string key);
  std::string  getKey();
  virtual bool  isGround() = 0;
  virtual bool  isAllie() = 0;
  virtual bool  isNeutral() = 0;
  virtual bool  isEnnemy() = 0;
  virtual void  setAttribute(std::string attribute, int valeur) = 0;
  virtual void  setAttribute(std::string attribute, std::string valeur) = 0;
  virtual int  getAttribute(std::string attribute) = 0;
  virtual Competence* getSkill(int index) = 0;
  ElementType getType();
   Element(int id, ElementType type);
  virtual Element* clone() = 0;
  void setClasse(Classe c);
  const Classe getClasse() const;

};

};

#endif // defined __ELEMENT_H__
