#ifndef FODUS_TILE_FACTORY_HPP
#define FODUS_TILE_FACTORY_HPP

#include "../../lib/rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "Tile.hpp"
#include "../bootstrap/Bootstrap.hpp"

class TileFactory
{
public:
	TileFactory(Bootstrap*);
	~TileFactory();
private:
    Bootstrap* m_boot;
	std::shared_ptr<rapidjson::Document> _tilesDoc;
    rapidjson::Value* getFactoryFor(std::string);
public:
	void setTilesDoc(rapidjson::Document*);
    std::shared_ptr<rapidjson::Document> getTilesDoc();
    void registerFacto(std::string key );
    Tile* buildTileForElt(std::string key);
    void loadTilesDoc(const std::string&);

};

#endif //FODUS_TILE_FACTORY_HPP