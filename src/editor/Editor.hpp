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
#include "../render/TileFactory.hpp"

class Editor
{
public:
	Editor();
	~Editor();
	void new_level();
	void load_level();
	void load_elts();
	void load_tiles();
	void run();
	void setFile(std::string);
	ElementList* getList();
	ElementList* getEditorList();
	void setElt(Element& elt, int x, int y, int depth = 0);
	Element* getElt(int x, int y, int depth);
	void save();

private:
	std::string m_file;
	ElementList* m_list;
	ElementList* m_editor_list;
	rapidjson::Document* m_level;
};

