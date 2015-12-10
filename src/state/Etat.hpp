// Etat.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class Etat
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


#ifndef __ETAT_H__
#define __ETAT_H__


#include "../global.hpp"
#include "../engine/Subject.hpp"
#include "ElementList.hpp"


namespace state {

class Etat: public engine::Subject{
private:
private:
  int  taille;
  int  turnsCount;
  bool  gameEnded;
  int  m_score;
public:
  ElementList liste;

public:
   Etat(int turn);
   ~Etat();
  void  setTaille(int newTaille);
  int  getTaille();
  void  setAttribute(std::string attribute, int valeur, int uid);
  void  setAttribute(std::string attribute, std::string valeur, int uid);
  int  getAttribute(std::string attribute, int uid);
  const int  getTurn();
  void  nextTurn();
  std::vector<int>  getEnnemies();
  std::vector<int>  getAllies();
  std::vector<int>  getNeutral();
  std::vector<int>  getGround();
  void  notify();
  int  getSize();
  void  setResult(int r);
  bool  hasWin();
  bool  hasEnded();
  ElementList* getList();

};

};

#endif // defined __ETAT_H__
