#include "Layer.hpp"



Layer::Layer()
{
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(WIDTH * HEIGHT * 4);
	resetVertices();
}


Layer::~Layer()
{
}

bool Layer::loadTileset(std::string Tilesetpath)
{
	if (!m_tileset.loadFromFile(Tilesetpath)) return false;
	return true;
}


void Layer::resetVertices()
{
	for (unsigned int i = 0; i < WIDTH; ++i)
		for (unsigned int j = 0; j < HEIGHT; ++j)
		{
			// Pointer to the current quad
			sf::Vertex* quad = &m_vertices[(i + j * WIDTH) * 4];

			quad[0].position = sf::Vector2f(i * SIZE, j * SIZE);
			quad[1].position = sf::Vector2f((i + 1) * SIZE, j * SIZE);
			quad[2].position = sf::Vector2f((i + 1) * SIZE, (j + 1) * SIZE);
			quad[3].position = sf::Vector2f(i * SIZE, (j + 1) * SIZE);

			quad[0].texCoords = sf::Vector2f(0,0);
			quad[1].texCoords = sf::Vector2f(SIZE,0);
			quad[2].texCoords = sf::Vector2f(SIZE,SIZE);
			quad[3].texCoords = sf::Vector2f(0,SIZE);
		}
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_tileset;
	target.draw(m_vertices, states);
}

