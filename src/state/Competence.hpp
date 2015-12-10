// Competence.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 02:02
//
//
// This header file defines the interfaces to the class Competence
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


#ifndef __COMPETENCE_H__
#define __COMPETENCE_H__


#include "../global.hpp"


namespace state {

class Competence{
private:
public:
  SkillType  type;
  int  damage;
  int  interest;
  int  target;
  int  range;
  int  cooldown;
  int  maxCooldown;

public:
   Competence(SkillType newType, int newDamage, int newTarget, int newInterest, int newRange, int newCooldown);
   Competence(SkillType newType, int newDamage, int newTarget, int newInterest, int newRange, int newCooldown, int newActualCooldown);
   ~Competence();
  void  used();

};

};

#endif // defined __COMPETENCE_H__
