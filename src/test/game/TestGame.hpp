#pragma once
#include "../../../lib/rapidjson/document.h"
#include "../../state/ElementList.hpp"

#include "../global.hpp"
#include "../../bootstrap/Bootstrap.hpp"
#include "../../render/TileFactory.hpp"
#include "../../render/AnimatedSprite.hpp"

class TestGame
{
public:
	TestGame();
	~TestGame();
	static AnimatedSprite m_animated_sprite;
	static AnimatedSprite m_animated_sprite2;
	static rapidjson::Document test_load_json_level();
	static void test_load_elt_list(ElementList*, Bootstrap*);
	static void test_load_tiles();
};

