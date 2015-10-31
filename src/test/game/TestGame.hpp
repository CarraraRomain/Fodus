#pragma once
#include "../../../lib/rapidjson/document.h"
#include "../../state/ElementList.hpp"

#include "../global.hpp"

class TestGame
{
public:
	TestGame();
	~TestGame();
	static rapidjson::Document test_load_json_level();
	static void test_load_elt_list(ElementList*);
	static void test_load_tiles();
};

