#ifndef FODUS_TILE_FACTORY_HPP
#define FODUS_TILE_FACTORY_HPP

#include "../../lib/rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "Tile.hpp"

class TileFactory
{
public:
	TileFactory(std::string);
	~TileFactory();
private:
	rapidjson::Document* _tilesDoc;
    rapidjson::Value* getFactoryFor(std::string);
public:
	void setTilesDoc(rapidjson::Document*);
    rapidjson::Document* getTilesDoc();
    void registerFacto(std::string key );
    Tile* buildTileForElt(std::string key);
    void loadTilesDoc(std::string path);

};

#endif;
