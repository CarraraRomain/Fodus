#pragma once
#include "Layer.hpp"
#include "../engine/Observer.hpp"

class InfoLayer :
	public Layer,
	public Observer
{
public:
	InfoLayer(Bootstrap* boot, Subject* sub);
	~InfoLayer();
	virtual void update(ObsType) override;
	virtual void update(const ElementList& list) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::map<int, sf::Text> m_perso_texts;
	sf::Font m_font;
	std::map<int, bool> m_display_texts;
};

