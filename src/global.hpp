#pragma once

#include <memory>

/* RapidJSON lib (fast header only lib) | Tested using v1.0.2
Lib is included in ../lib/rapidjson
URL : https://github.com/miloyip/rapidjson
*/
#define RAPIDJSON_HAS_STDSTRING 1
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/writer.h"
#include "../lib/rapidjson/prettywriter.h"
#include "../lib/rapidjson/stringbuffer.h"


/* SFML Library | Tested using v2.3.2 / 2.3.1
URL : http://www.sfml-dev.org/
*/
#include <SFML/Graphics.hpp>

/* EasyLogging++ lib | v9.81
Logging library. Has to be include at the top of the file
*/

#define ELPP_NO_DEFAULT_LOG_FILE
#include "../lib/easylogging/easylogging++.h"

#define GLOBAL_CONF_FILE "../../res/config/config.json"
#define JSON_TILES_INDEX "../../res/GFX/tiles.json"
#define SIZE 32
#define WIDTH 24
#define HEIGHT 16


