//
// Created by achille on 13/10/15.
//

#ifndef FODUS_MAIN_HPP
#define FODUS_MAIN_HPP

// config.h includes build & project config parameters
#include "config.h"

#include <iostream>
#include <fstream>
#include <sstream>

/* RapidJSON lib (fast header only lib) | Tested using v1.0.2
Lib is included in ../lib/rapidjson
URL : https://github.com/miloyip/rapidjson
*/
#include "../lib/rapidjson/document.h"

#include "../lib/rapidjson/writer.h"
#include "../lib/rapidjson/stringbuffer.h"
/* SFML Library | Tested using v2.3.2 / 2.3.1
URL : http://www.sfml-dev.org/
*/
#include <SFML/Graphics.hpp>

#include "render/TileFactory.hpp"
#include <unistd.h>
#include <vector>
#include <string>

int main(int argc, char* argv[]);

void test_load_tiles();
void test_sfml();

std::vector<sf::Sprite> test_load_level(sf::RenderWindow&);

#endif //FODUS_MAIN_HPP
