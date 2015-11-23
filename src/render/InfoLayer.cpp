#include "InfoLayer.hpp"
#include "Scene.hpp"


InfoLayer::InfoLayer(Bootstrap* boot, Subject* sub): Layer(boot), Observer(sub)
{
	if (!m_font.loadFromFile(m_boot->getPath("font"))) LOG(FATAL) << "Font not found";

}


InfoLayer::~InfoLayer()
{
}

void InfoLayer::update(ObsType type)
{
	if(type == ObsAnimation)
	{
		Scene* s = dynamic_cast<Scene*>(m_sub);
		m_display_texts.clear();
		for (auto sp : s->getAnims()->m_sprites)
		{
			if (s->getAnims()->isAnimationRunning(sp.first)) m_display_texts[sp.first] = false;
			else m_display_texts[sp.first] = true;
		}

	}
}

void InfoLayer::update(const ElementList& list)
{
	int uid(0);
	m_perso_texts.clear();
	for (auto it = list.begin(); it != list.end();++it)
	{
		if(it->get()->type == Mobile)
		{
			Perso* ptr = dynamic_cast<Perso*>(it->get());
			uid = ptr->getUid();
			m_perso_texts[uid] = sf::Text();
			m_perso_texts[uid].setString(std::to_string(ptr->getAttribute("currentHealth")));
			m_perso_texts[uid].setFont(m_font);
			m_perso_texts[uid].setColor(sf::Color::Red);
			m_perso_texts[uid].setCharacterSize(14);
			m_perso_texts[uid].setPosition((OFFSET_X+ptr->getX())*SIZE,
				(1+OFFSET_Y+ptr->getY())*SIZE);
		}
	}
	
}

void InfoLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto txt : m_perso_texts)
	{
		if(m_display_texts.at(txt.first)) target.draw(txt.second, states);
	}
}