#include "ElementLayer.hpp"



ElementLayer::ElementLayer(std::string JSONpath)
{
	m_tile_factory = new TileFactory(JSONpath);
    loadTileset("../../res/GFX/tileset0.png");
}


ElementLayer::~ElementLayer()
{
	delete m_tile_factory;
}


void ElementLayer::update(ElementList* list)
{
	int X = 0;
	int Y = 0;

	for (int i = 0; i < list->size();i++)
	{
		Element* elt = (*list)[i];
	
		X = elt->getX();
		Y = elt->getY();
		sf::Vertex* quad = &m_vertices[(X + Y * WIDTH) * 4];
		//Tile* tile = m_tile_factory->buildTileForElt(elt.getKey());
		Tile* tile = m_tile_factory->buildTileForElt(elt->getKey());

		quad[0].texCoords = sf::Vector2f(tile->getX(), tile->getY());
		quad[1].texCoords = sf::Vector2f(tile->getX()+SIZE, tile->getY());
		quad[2].texCoords = sf::Vector2f(tile->getX() + SIZE, tile->getY()+SIZE);
		quad[3].texCoords = sf::Vector2f(tile->getX(), tile->getY() + SIZE);
		
	}

}
