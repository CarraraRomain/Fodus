#include <stdexcept>
#include "TileFactory.hpp"



TileFactory::TileFactory(std::string path) {
loadTilesDoc(path);
}

TileFactory::~TileFactory()
{
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
        if (_tilesDoc->Parse(ss.str().c_str()).HasParseError()) throw std::invalid_argument("JSON bad encoding");
        std::cout << ss.str();
    }
    else
    {
        std::cout << "Bad" << std::endl;
    }
    ifs.close();
}


Tile* TileFactory::buildTileForElt(std::string key) {

    rapidjson::Value::ConstMemberIterator node = _tilesDoc->FindMember(key);
    if (itr == document.MemberEnd()){
        node = _tilesDoc->FindMember("UNDEFINED");
    }
    Tile* tile = new Tile(&node->value);
    return tile;
}


rapidjson::Value *TileFactory::getFactoryFor(std::string key) {
    return nullptr;
}
