#include <stdexcept>
#include "TileFactory.hpp"



TileFactory::TileFactory(Bootstrap* boot) : m_boot(boot){
    LOG(DEBUG) << "Creating factory";
    _tilesDoc.reset(new rapidjson::Document());
    loadTilesDoc("tiles_index");
    LOG(DEBUG) << "Factory ready";
}

TileFactory::~TileFactory()
{
}

std::shared_ptr<rapidjson::Document> TileFactory::getTilesDoc() {
    return _tilesDoc;
}


void TileFactory::registerFacto(std::string key) {

}

void TileFactory::loadTilesDoc(const std::string& name) {
    _tilesDoc = m_boot->getDocument(name);

}


Tile* TileFactory::buildTileForElt(std::string key) {

    rapidjson::Value& node = ((*_tilesDoc)["tiles"].HasMember(key.c_str()))?
                             (*_tilesDoc)["tiles"][key.c_str()]:
                             (*_tilesDoc)["tiles"]["UNDEFINED"];
    Tile* tile = new Tile(node);
    return tile;
}


rapidjson::Value *TileFactory::getFactoryFor(std::string key) {
    return nullptr;
}
