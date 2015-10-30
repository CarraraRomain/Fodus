#pragma once

#include "../state/ElementList.hpp"
#include "../global.hpp"
#include <SFML/Graphics.hpp>
#include "../../lib/rapidjson/document.h"
#include "../lib/rapidjson/prettywriter.h"
#include "../lib/rapidjson/stringbuffer.h"
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


class Editor
{
public:
	Editor();
	~Editor();
	void load_gui();
	void new_level();
	void load_level();
	void load_elts();
	void load_tiles();
	void load();
	void run();
	void setFile(std::string);
	ElementList* getList();
	ElementList* getEditorList();
	void setElt(Element elt, int x, int y, int depth = 0);
	Element getElt(int x, int y, int depth);
	void save();
	void level_event_loop();
	void editor_event_loop();

private:
	// graphics
	std::unique_ptr<sf::RenderWindow> m_level_window;
	std::unique_ptr<sf::RenderWindow> m_editor_window;
	std::unique_ptr<Scene> m_level_scene;
	std::unique_ptr<Scene> m_editor_scene;
	std::unique_ptr<SelectBox> m_box;
	std::unique_ptr<Element> m_selected_elt;
	std::string m_file;
	
	ElementList* m_list;
	ElementList* m_editor_list;
	rapidjson::Document* m_level;
	
};

