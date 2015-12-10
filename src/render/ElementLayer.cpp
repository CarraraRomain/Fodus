#include "ElementLayer.hpp"

using namespace render;

ElementLayer::ElementLayer(boot::Bootstrap* boot, int depth): Layer(boot), m_depth(depth)
{
	LOG(DEBUG) << "Creating EltLayer";
	m_tile_factory.reset(new TileFactory(m_boot));
    loadTileset("tileset 0");
	LOG(DEBUG) << "EltLayer ready";
}


ElementLayer::~ElementLayer()
{
}


void ElementLayer::update(const state::ElementList& list)
{
	LOG(DEBUG) << "Updating layer";
	int X = 0;
	int Y = 0;
	int depth = 0;
	for (int i = 0; i < int(list.size());i++)
	{
		if (list[i]->type != Fixed) continue;
		X = list[i]->getX();
		Y = list[i]->getY();
		if(list[i]->getD() == m_depth)
		{
			sf::Vertex* quad = &m_vertices[(X + Y * WIDTH) * 4];

			Tile* tile = m_tile_factory->buildTileForElt(list[i]->getKey());

			quad[0].texCoords = sf::Vector2f(tile->getX(), tile->getY());
			quad[1].texCoords = sf::Vector2f(tile->getX() + SIZE, tile->getY());
			quad[2].texCoords = sf::Vector2f(tile->getX() + SIZE, tile->getY() + SIZE);
			quad[3].texCoords = sf::Vector2f(tile->getX(), tile->getY() + SIZE);
			delete tile;
		}
		
	}

}
