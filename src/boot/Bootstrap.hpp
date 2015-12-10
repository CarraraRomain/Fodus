// Bootstrap.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 15:43
//
//
// This header file defines the interfaces to the class Bootstrap
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


#ifndef __BOOTSTRAP_H__
#define __BOOTSTRAP_H__


#include "../global.hpp"
#include "../engine/ModeCommand.hpp"


namespace boot {

class Bootstrap: public engine::CommandReceiver{
private:
private:
  int  m_argc;
  rapidjson::Document  m_config;
  char** m_argv;
  std::map<std::string, std::shared_ptr<rapidjson::Document>> m_docs;
  std::map<std::string, std::shared_ptr<rapidjson::Document>> m_levels;
private:
  void  loadFile(const std::string& name);
  void  loadLevel(const std::string& name);
  bool  checkNode(const std::string& ) const;
  bool  checkLevelNode(const std::string& );
  void  launch_editor();
  void  launch_game();
public:
  void  handleCommand(engine::Command* c);
   Bootstrap(int argc, char** argv);
   Bootstrap();
   ~Bootstrap();
  void  loadConf();
  void  loadLevelIndex();
  void  start();
  void  listLevels();
  std::string  chooseLevel();
  void  run();
  void  getConfig(const std::string& ) const;
  void  saveDocument(const std::string& , const rapidjson::Document& );
  std::string  getPath(const std::string& );
  std::shared_ptr<rapidjson::Document> getDocument(const std::string& );
  std::shared_ptr<rapidjson::Document> getLevel(const std::string& );

};

};

#endif // defined __BOOTSTRAP_H__
