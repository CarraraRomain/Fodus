// Perso.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-09 22:14
//
//
// This header file defines the interfaces to the class Perso
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


#ifndef __PERSO_H__
#define __PERSO_H__


#include "../global.hpp"
#include "Element.hpp"


namespace state {

class Perso: public Element{
private:
private:
  std::string  nom;
  int  side;
  int  health;
  int  defence;
  int  power;
  int  move;
  int  corruption;
  int  status;
  int  range;
  int  currentHealth;
  int  zombiLimit;
  int  level;
  int  conversion;
  AnimationType  direction;
  int  owner;
  Classe classe;
public:
   Perso(int id, int player);
  Element* clone();
   ~Perso();
  virtual bool  isAllie();
  virtual bool  isEnnemy();
  virtual bool  isNeutral();
  virtual bool  isGround();
  AnimationType  getDir();
  const int  getOwner();
  virtual void  setAttribute(std::string attribute, int valeur);
  virtual void  setAttribute(std::string attribute, std::string valeur);
  virtual int  getAttribute(std::string attribute);
  virtual Competence* getSkill(int i);
  void  addSkill(state::Competence* skill);
  int  nbrSkill();

};

};

#endif // defined __PERSO_H__
