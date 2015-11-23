#pragma once
#include "Layer.hpp"
class InfoLayer :
	public Layer
{
public:
	InfoLayer(Bootstrap* boot);
	~InfoLayer();
	virtual void update(const ElementList& list) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::map<int, sf::Text> m_perso_texts;
	sf::Font m_font;
};

