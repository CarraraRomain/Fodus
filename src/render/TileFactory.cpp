#include <stdexcept>
#include "TileFactory.hpp"



TileFactory::TileFactory(std::string path) {
    _tilesDoc = new rapidjson::Document();
    loadTilesDoc(path);
}

TileFactory::~TileFactory()
{
    delete(_tilesDoc);
}

rapidjson::Document* TileFactory::getTilesDoc() {
    return _tilesDoc;
}

void TileFactory::setTilesDoc(rapidjson::Document* tilesDoc){
    _tilesDoc = tilesDoc;
}

void TileFactory::registerFacto(std::string key) {

}

void TileFactory::loadTilesDoc(std::string path) {
    std::stringstream ss;
    std::ifstream ifs;
    ifs.open(path, std::ios::binary);
    if(ifs.is_open())
    {
        std::cout << "Good" << std::endl;
        ss << ifs.rdbuf(); // 1
        std::cout << "Done" << std::endl;
        if (_tilesDoc->Parse<0>(ss.str().c_str()).HasParseError()) throw std::invalid_argument("JSON bad encoding");
        std::cout << ss.str();
    }
    else
    {
        std::cout << "Bad" << std::endl;
        exit(-1);
    }
    ifs.close();
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
