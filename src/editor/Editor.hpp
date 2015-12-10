#pragma once

#include "../state/ElementList.hpp"
#include "../global.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
/*
* SFML
*/
#include <SFML/Graphics.hpp>


/*
 * 
 */
#include "../render/TileFactory.hpp"
#include "../render/Scene.hpp"
#include "SelectBox.hpp"
#include "../boot/Bootstrap.hpp"
#include "../state/Case.hpp"

class Editor
{
public:
	Editor(boot::Bootstrap*);
	~Editor();
	void load_gui();
	void new_level();
	void load_level();
	void load_elts();
	void load_tiles();
	void load();
	void run();
	void setFile(std::string);
	void setElt(state::Case elt, int x, int y, int depth = 0);
	state::Case getElt(int x, int y, int depth);
	void save();
	void level_event_loop();
	void editor_event_loop();

private:
	boot::Bootstrap* m_boot;

	std::unique_ptr<sf::RenderWindow> m_level_window;
	std::unique_ptr<sf::RenderWindow> m_editor_window;
	std::unique_ptr<render::Scene> m_level_scene;
	std::unique_ptr<render::Scene> m_editor_scene;
	
	std::unique_ptr<SelectBox> m_box;
	std::unique_ptr<state::Case> m_selected_elt;
	
	std::unique_ptr<state::ElementList> m_level_list;
	std::unique_ptr<state::ElementList> m_editor_list;
	
	std::shared_ptr<rapidjson::Document> m_level;
	std::string m_file;
};

