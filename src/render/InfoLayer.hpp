#pragma once
#include "Layer.hpp"
#include "../engine/Observer.hpp"
#include "../game/Coord.hpp"

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
	void updateVertices();
	void setPlayer(int x, int y);
	int relax(int x, int y, int vx, int vy);
	void ford(int x, int y);
	void disable();
	void enable();
	void hideMoveMap();
	void showMoveMap();
	void syncMoveMap();
	void syncMoveMap(std::vector<std::vector<int>>& map);
	void resetMoveMap();

private:
	std::map<int, sf::Text> m_perso_texts;
	sf::Font m_font;
	sf::Vector2i m_player;
	int move_qty;
	std::map<int, bool> m_display_texts;
	bool m_disable_actions;
	std::vector<Coord*> m_coords;
	std::vector<std::vector<int>> m_map;
	bool m_show_map;
};

