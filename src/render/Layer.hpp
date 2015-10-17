#pragma once

#include "SFML/Graphics.hpp"
#include "../global.hpp"

class Layer :
	sf::Drawable
{
public:
	Layer();
	~Layer();
	bool loadTileset(std::string Tilesetpath);
	void resetVertices();
	

protected:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

