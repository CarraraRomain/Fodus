//
// Created by Achille on 12/10/2015.
//

#ifndef FODUS_TILE_HPP
#define FODUS_TILE_HPP

#include "../../lib/rapidjson/document.h"

class Tile {
public:
    Tile(const rapidjson::Value&);

    ~Tile();

private:
    int _id;
    std::string _key;
    int _x;
    int _y;
    int _width;
    int _height;
    int _tileNumber;


public:
    int getId() const;

    void setId(int id);

    const std::string &getKey() const;

    void setKey(const std::string &_key);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int getTileNumber() const;

    void setTileNumber(int tileNumber);

};
#endif //FODUS_TILE_HPP
