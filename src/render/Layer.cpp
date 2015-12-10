#include "Layer.hpp"

using namespace render;

Layer::Layer(boot::Bootstrap* boot): m_boot(boot)
{
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(WIDTH * HEIGHT * 4);
	resetVertices();
}


Layer::~Layer()
{
}

bool Layer::loadTileset(std::string tileset)
{
	sf::Image image;
	if (!image.loadFromFile(m_boot->getPath(tileset))) return false;
	image.createMaskFromColor(sf::Color::Black);
	m_tileset.loadFromImage(image);
	
	return true;
}


void Layer::resetVertices()
{
	for (unsigned int i = 0; i < WIDTH; ++i)
		for (unsigned int j = 0; j < HEIGHT; ++j)
		{
			// Pointer to the current quad
			sf::Vertex* quad = &m_vertices[(i + j * WIDTH) * 4];

			quad[0].position = sf::Vector2f(96+i * SIZE			, 96 + j * SIZE);
			quad[1].position = sf::Vector2f(96+(i + 1) * SIZE	, 96 + j * SIZE);
			quad[2].position = sf::Vector2f(96+(i + 1) * SIZE	, 96+ (j + 1) * SIZE);
			quad[3].position = sf::Vector2f(96+i * SIZE			, 96+ (j + 1) * SIZE);

			quad[0].texCoords = sf::Vector2f(0,0);
			quad[1].texCoords = sf::Vector2f(SIZE,0);
			quad[2].texCoords = sf::Vector2f(SIZE,SIZE);
			quad[3].texCoords = sf::Vector2f(0,SIZE);
		}
}

void Layer::clearVertices()
{
	for (unsigned int i = 0; i < WIDTH; ++i)
		for (unsigned int j = 0; j < HEIGHT; ++j)
		{
			// Pointer to the current quad
			sf::Vertex* quad = &m_vertices[(i + j * WIDTH) * 4];


			quad[0].texCoords = sf::Vector2f(3*SIZE, 0);
			quad[1].texCoords = sf::Vector2f(4*SIZE, 0);
			quad[2].texCoords = sf::Vector2f(4*SIZE, SIZE);
			quad[3].texCoords = sf::Vector2f(3 * SIZE, SIZE);
		}
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_tileset;
	target.draw(m_vertices, states);
}

