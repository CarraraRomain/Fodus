#pragma once
#include "Layer.hpp"
#include "TileFactory.hpp"
#include "../state/LegacyElementList.hpp"
#include "../global.hpp"

class ElementLayer :
	public Layer
{
public:
	ElementLayer(Bootstrap*, int);
	~ElementLayer();
	virtual void update(const LegacyElementList& list) override;

private:
	int m_depth;
	std::unique_ptr<TileFactory> m_tile_factory;
};

