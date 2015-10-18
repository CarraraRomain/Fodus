#include "ElementLayer.hpp"



ElementLayer::ElementLayer(std::string JSONpath)
{
	m_tile_factory = new TileFactory(JSONpath);
}


ElementLayer::~ElementLayer()
{
	delete m_tile_factory;
}


void ElementLayer::update(ElementList list)
{
	int X = 0;
	int Y = 0;

	for (;;)
	{
		Element elt;
		X = elt.getX();
		Y = elt.getY();
		
		sf::Vertex* quad = &m_vertices[(X + Y * WIDTH) * 4];
		quad[0].position = sf::Vector2f(X, Y);
		quad[1].position = sf::Vector2f(X + SIZE, Y);
		quad[2].position = sf::Vector2f(X + SIZE, Y + SIZE);
		quad[3].position = sf::Vector2f(X, Y + SIZE);

		//Tile* tile = m_tile_factory->buildTileForElt(elt.getKey());
		Tile* tile = m_tile_factory->buildTileForElt("UNDEFINED");
		
		quad[0].texCoords = sf::Vector2f(tile->getX(), tile->getY());
		quad[1].texCoords = sf::Vector2f(tile->getX()+SIZE, tile->getY());
		quad[2].texCoords = sf::Vector2f(tile->getX() + SIZE, tile->getY()+SIZE);
		quad[3].texCoords = sf::Vector2f(tile->getX(), tile->getY() + SIZE);
		
	}

}
