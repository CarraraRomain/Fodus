#pragma once
#include "Layer.hpp"
#include "TileFactory.hpp"
#include "../state/ElementList.hpp"
#include "../global.hpp"

class ElementLayer :
	public Layer
{
public:
	ElementLayer(std::string JSONpath);
	~ElementLayer();
	virtual void update(ElementList* list) override;

private:
	TileFactory* m_tile_factory;
};

