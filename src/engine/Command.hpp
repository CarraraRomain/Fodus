// Command.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 16:55
//
//
// This header file defines the interfaces to the class Command
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


#ifndef __COMMAND_H__
#define __COMMAND_H__


#include "../global.hpp"
#include "CommandReceiver.hpp"


namespace engine {

class Command{
private:
protected:
  CommandReceiver* m_command_receiver;
public:
  const int  player;
  const CommandType type;

public:
   Command(CommandReceiver* command_receiver, CommandType type, int player = 0);
   ~Command();
  virtual void  execute() = 0;

};

};

#endif // defined __COMMAND_H__
