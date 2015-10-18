//
// Created by Achille on 12/10/2015.
//

#include "Tile.hpp"
#include "../../lib/rapidjson/rapidjson.h"



Tile::Tile(const rapidjson::Value& node) {
    // Text. x | y are reversed compared to
    // the "logical" orientation
    _x = node["x"].GetInt()*32;
    _y = node["y"].GetInt()*32;
}

Tile::~Tile(){


}


int Tile::getId() const {
    return _id;
}

void Tile::setId(int id) {
    _id = id;
}

const std::string &Tile::getKey() const {
    return _key;
}

void Tile::setKey(const std::string &key) {
    _key = key;
}

int Tile::getX() const {
    return _x;
}

void Tile::setX(int x) {
    _x = x;
}

int Tile::getY() const {
    return _y;
}

void Tile::setY(int y) {
    y = y;
}

int Tile::getWidth() const {
    return _width;
}

void Tile::setWidth(int width) {
    _width = width;
}

int Tile::getHeight() const {
    return _height;
}

void Tile::setHeight(int height) {
    _height = height;
}

int Tile::getTileNumber() const {
    return _tileNumber;
}

void Tile::setTileNumber(int tileNumber) {
    _tileNumber = tileNumber;
}