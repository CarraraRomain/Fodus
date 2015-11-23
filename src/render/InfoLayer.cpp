#include "InfoLayer.hpp"



InfoLayer::InfoLayer(Bootstrap* boot): Layer(boot)
{
	if (!m_font.loadFromFile(m_boot->getPath("font"))) LOG(FATAL) << "Font not found";

}


InfoLayer::~InfoLayer()
{
}

void InfoLayer::update(const ElementList& list)
{
	int uid(0);
	for (auto it = list.begin(); it != list.end();++it)
	{
		if(it->get()->type == Mobile)
		{
			Perso* ptr = dynamic_cast<Perso*>(it->get());
			uid = ptr->getUid();
			m_perso_texts[uid] = sf::Text();
			m_perso_texts[uid].setString(std::to_string(ptr->getAttribute("currentHealth")));
			m_perso_texts[uid].setFont(m_font);
			m_perso_texts[uid].setColor(sf::Color::White);
			m_perso_texts[uid].setCharacterSize(14);
			m_perso_texts[uid].setPosition((OFFSET_X+ptr->getX())*SIZE,
				(OFFSET_Y+ptr->getY())*SIZE);
		}
	}
	
}

void InfoLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto txt : m_perso_texts)
	{
		target.draw(txt.second, states);
	}
}