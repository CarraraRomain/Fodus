#pragma once
#include "../../../lib/rapidjson/document.h"
#include "../../state/LegacyElementList.hpp"

#include "../global.hpp"
#include "../../bootstrap/Bootstrap.hpp"
#include "../../render/TileFactory.hpp"

class TestGame
{
public:
	TestGame();
	~TestGame();
	static rapidjson::Document test_load_json_level();
	static void test_load_elt_list(LegacyElementList*, Bootstrap*);
	static void test_load_tiles();
};

