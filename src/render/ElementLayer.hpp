#pragma once
#include "Layer.hpp"
#include "TileFactory.hpp"
#include "../state/ElementList.hpp"
#include "../global.hpp"

class ElementLayer :
	public Layer
{
public:
	ElementLayer(int depth, std::string JSONpath);
	~ElementLayer();
	virtual void update(const ElementList& list) override;

private:
	int m_depth;
	TileFactory* m_tile_factory;
};

