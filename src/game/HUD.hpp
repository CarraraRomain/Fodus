#pragma once
#include "../global.hpp"
#include "../bootstrap/Bootstrap.hpp"
#include "../engine/Subject.hpp"

class HUD :
	public sf::Drawable
{
public:
	HUD(Bootstrap* boot);
	~HUD();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void load(sf::Vector2u window_size);
	void updateTurns(const int);
	void updateMoveCapa(bool);
	void updateAttackCapa(bool);
	void turnFinished();
	void newTurn();
	void actionsDisabled();
	void actionsEnabled();

private:
	Bootstrap* m_boot;
	sf::Vector2u m_window_size;
	// Font
	sf::Font m_font;
	// Texts
	std::map<std::string, sf::Text> m_text_map;
	sf::Texture m_dashboard_texture;
	sf::RectangleShape m_dashboard;

	int m_turns;
	bool m_disable_action;
	void setFont(std::string key);
};

