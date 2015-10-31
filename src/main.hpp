//
// Created by achille on 13/10/15.
//

#ifndef FODUS_MAIN_HPP
#define FODUS_MAIN_HPP



// config.h includes build & project config parameters
#include "config.h"
#include "global.hpp"

// Standard Lib
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


/* SFML Library | Tested using v2.3.2 / 2.3.1
URL : http://www.sfml-dev.org/
*/
#include <SFML/Graphics.hpp>

// Project includes
#include "bootstrap/Bootstrap.hpp"
#include "editor/Editor.hpp"
#include "render/TileFactory.hpp"
#include "render/Scene.hpp"

// Easylogging startup macro
INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]);

void test_load_tiles();
void test_sfml();

void launch_editor(std::shared_ptr<Bootstrap>);
void launch_game(std::shared_ptr<Bootstrap>);

std::vector<sf::Sprite> test_load_level(sf::RenderWindow&);
rapidjson::Document test_load_json_level();
void test_load_elt_list(ElementList*);
#endif //FODUS_MAIN_HPP
