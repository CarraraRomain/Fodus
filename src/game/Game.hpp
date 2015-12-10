// Game.hpp
// 
// Project: Fodus
// Version: 3.1
// Author: Timothe Perez, Romain Carrara, Zhuo Li
// Auto-Generated Date: 2015-12-10 15:43
//
//
// This header file defines the interfaces to the class Game
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


#ifndef __GAME_H__
#define __GAME_H__


#include "../global.hpp"
#include "../engine/SkillCommand.hpp"
#include "../render/Scene.hpp"
#include "../state/Perso.hpp"
#include "HUD.hpp"
#include "IGame.hpp"


namespace game {

class Game: public IGame{
private:
private:
  HUD  m_hud;
  render::Scene  m_game_scene;
  state::Perso* m_selected_perso;
  sf::RectangleShape  m_select_box;
  bool  m_show_box;
  int  m_client_id;
  bool  m_isKeyPressed;
  int  m_turns;
  bool  m_end;
  bool  m_has_played;
  bool  is_playing;
  int  skillMode;
public:
  std::unique_ptr<sf::RenderWindow> m_game_window;
  std::unique_ptr<rapidjson::Document> m_game_level;
  std::map<int, bool> m_move_watcher;

private:
  void  game_event_loop();
  void  updateHUD();
  void  endPlayerTurn();
  void  watchMovements(int pid);
  void  disableActions();
  void  enableActions();
  void  reflowSkill();
public:
   Game(boot::Bootstrap* boot, engine::AbstractEngine* engine, int cid);
   ~Game();
  void  load_gui();
  void  load();
  void  run();
  void  draw();
  void  start();
  void  syncRequest();
  void  whoIsPlaying();
  void  update(ObsType type);
  void  updateGlobal(state::Etat& e);
  void  updateElement(state::Element& el);
  void  updateTurn(int turn);
  void  updatePlayer(engine::Player pl);
  void  updateGameEnd(int score);
  void  updateNowPlaying(int pid);
  void  canPlay(int pid);
  void  hasPlayed(int pid);
  void  sync(state::ElementList list);

};

};

#endif // defined __GAME_H__
