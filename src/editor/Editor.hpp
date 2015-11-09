#pragma once

#include "../state/LegacyElementList.hpp"
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
#include "../bootstrap/Bootstrap.hpp"

class Editor
{
public:
	Editor(Bootstrap*);
	~Editor();
	void load_gui();
	void new_level();
	void load_level();
	void load_elts();
	void load_tiles();
	void load();
	void run();
	void setFile(std::string);
	void setElt(LegacyElement elt, int x, int y, int depth = 0);
	LegacyElement getElt(int x, int y, int depth);
	void save();
	void level_event_loop();
	void editor_event_loop();

private:
	Bootstrap* m_boot;

	std::unique_ptr<sf::RenderWindow> m_level_window;
	std::unique_ptr<sf::RenderWindow> m_editor_window;
	std::unique_ptr<Scene> m_level_scene;
	std::unique_ptr<Scene> m_editor_scene;
	
	std::unique_ptr<SelectBox> m_box;
	std::unique_ptr<LegacyElement> m_selected_elt;
	
	std::unique_ptr<LegacyElementList> m_level_list;
	std::unique_ptr<LegacyElementList> m_editor_list;
	
	std::shared_ptr<rapidjson::Document> m_level;
	std::string m_file;
};
