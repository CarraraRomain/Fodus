// ElementList.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 15:43
//
//
// This header file defines the interfaces to the class ElementList
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


#ifndef __ELEMENTLIST_H__
#define __ELEMENTLIST_H__


#include "../global.hpp"
#include "Element.hpp"


namespace state {

class ElementList{
private:
public:
  std::vector<std::unique_ptr<Element> > m_elements;
  typedef std::vector<std::unique_ptr<Element>>::iterator iterator;
  typedef std::vector<std::unique_ptr<Element>>::const_iterator const_iterator;

public:
   ElementList();
   ElementList(const ElementList& list);
   ElementList(ElementList&& list);
   ~ElementList();
  void  push_back(Element* elt);
  void  clear();
  void  setAttribute(std::string attribut, int valeur, int uid);
  void  setAttribute(std::string attribut, std::string valeur, int uid);
  int  getAttribute(std::string attribute, int uid);
  Competence* getSkill(int uid, int index);
  int  findUid(int uid);
  void  erase(int uid);
  iterator  begin();
  iterator  end();
  const_iterator  begin() const;
  const_iterator  cbegin() const;
  const_iterator  end() const;
  const_iterator  cend() const;
  std::unique_ptr<Element>& operator[](size_t i);
  const 	std::unique_ptr<Element>& operator[](size_t i) const;
  size_t size() const;
  ElementList& operator=(const ElementList& list);
  ElementList& operator=(ElementList&& list);

};

};

#endif // defined __ELEMENTLIST_H__
