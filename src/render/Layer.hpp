#pragma once

#include "../global.hpp"
#include "../bootstrap/Bootstrap.hpp"
#include "../state/LegacyElementList.hpp"

class Layer :
	public sf::Drawable
{
public:
	Layer(Bootstrap*);
	~Layer();
	bool loadTileset(std::string Tilesetpath);
	void resetVertices();
	void clearVertices();
	virtual void update(const LegacyElementList& list) = 0;
	

protected:
	Bootstrap* m_boot;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

