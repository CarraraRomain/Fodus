#include "InfoLayer.hpp"
#include "Scene.hpp"
#include "../state/Case.hpp"


InfoLayer::InfoLayer(Bootstrap* boot, Subject* sub): Layer(boot), Observer(sub)
{
	if (!m_font.loadFromFile(m_boot->getPath("font"))) LOG(FATAL) << "Font not found";
	m_coords.resize(HEIGHT*WIDTH);
	resetVertices();
	m_disable_actions = true;
}


InfoLayer::~InfoLayer()
{
	for (Coord* c : m_coords) delete c;
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
	else if (type== ObsHUD)
	{
		
	}
}

void InfoLayer::update(const ElementList& list)
{
	int uid(0);
	m_perso_texts.clear();
	for (auto it = list.begin(); it != list.end();++it)
	{
		Element* ptr = it->get();
		int index = ptr->getX() + WIDTH*ptr->getY();
		if (m_coords[index] == nullptr) {
			Coord* c = new Coord(ptr->getX(), ptr->getY());
			m_coords.at(index) = c;
		}
		if ((ptr->getD() > 0 && ptr->getKey() != "VOID_1") || (!m_coords[index]->canMoveTo() && ptr->getD() == 0))
				m_coords[index]->setCannotMoveTo();
		else m_coords[index]->setCanMoveTo();
			m_coords[index]->setNotAttackable();
		
		

		if(it->get()->type == Fixed)
		{
		
		}
		else if(it->get()->type == Mobile)
		{
			Perso* ptr = dynamic_cast<Perso*>(it->get());
			uid = ptr->getUid();
			if (uid == 1)
			{
				setPlayer(ptr->getX(), ptr->getY());
				move_qty = ptr->getAttribute("move");
			}
			m_perso_texts[uid] = sf::Text();
			m_perso_texts[uid].setString(std::to_string(ptr->getAttribute("currentHealth")));
			m_perso_texts[uid].setFont(m_font);
			m_perso_texts[uid].setColor(sf::Color::Red);
			m_perso_texts[uid].setCharacterSize(14);
			m_perso_texts[uid].setPosition((OFFSET_X+ptr->getX())*SIZE,
				(1+OFFSET_Y+ptr->getY())*SIZE);
			int index = ptr->getX() + WIDTH*ptr->getY();
			if (ptr->isEnnemy() || ptr->isNeutral()) m_coords[index]->setAttackable();
			else m_coords[index]->setNotAttackable();
		}
	}
	syncMoveMap();
	//ford(m_player.x, m_player.y);
	updateVertices();
}

void InfoLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!m_disable_actions) target.draw(m_vertices, states);
	for (auto txt : m_perso_texts)
	{
		if(m_display_texts.at(txt.first)) target.draw(txt.second, states);
	}
}

void InfoLayer::updateVertices()
{
	clearVertices();
	int X(0), Y(0);
	LOG(DEBUG) << "Update info vertices";
	for(Coord* c: m_coords)
	{
		
		sf::Vertex* quad = &m_vertices[(c->x + c->y*WIDTH)*4];
		sf::Color col = (m_coords[c->x + c->y*WIDTH]->move_weight > 0 && m_show_map) ?
			sf::Color(0,255,0,42): sf::Color(255, 0, 0, 0);
		col = (c->isAttackable()) ? sf::Color(255, 0, 0, 42): col;
		quad[0].color = col;
		quad[1].color = col;
		quad[2].color = col;
		quad[3].color = col;
	}
}

void InfoLayer::setPlayer(int x, int y)
{
	m_player.x = x;
	m_player.y = y;
}

int InfoLayer::relax(int x, int y, int vx, int vy)
{
	if (vx<0 || vx >= WIDTH || vy < 0 || vy >= HEIGHT) return 0;
	int index = x + y*WIDTH;
	int vindex = vx + vy*WIDTH;

	if(m_coords[vindex]->move_weight > m_coords[index]->move_weight+1)
	{
		m_coords[vindex]->move_weight = m_coords[index]->move_weight + 1;
		//LOG(DEBUG) << "Relax with " << m_coords[vindex]->move_weight;
		return m_coords[vindex]->move_weight;
	}
	return 0;
}

void InfoLayer::ford(int x, int y)
{
	LOG(DEBUG) << "FORD : calculating move map";
	// ford starting at x, y
	int index = x + y*WIDTH;
	int thre(400);
	int i(0), count(0), t(0);
	// reset all map with huge value (infty)
	for (Coord* c : m_coords) c->move_weight = 999;
	m_coords[index]->move_weight = 0;
	bool converged(false);
	while(!converged)
	{
		if(m_coords[i]->canMoveTo()  || i == index)
		{
			int x = m_coords[i]->x;
			int y = m_coords[i]->y;
			
			t += relax(x, y, x - 1, y    );
			t += relax(x, y, x + 1, y    );
			t += relax(x, y, x    , y - 1);
			t += relax(x, y, x    , y + 1);
			
		}
		i = (i+1) % (WIDTH*HEIGHT);
		count++;
		// if we've been through all map
		// and no relax has been done (t==0), the algo has converged
		if (count > thre && t == 0)
			converged = true;
		else if (count > thre) {
			t = 0;
			count = 0;
		}
	}
}

void InfoLayer::disable()
{
	m_disable_actions = true;
}

void InfoLayer::enable()
{
	m_disable_actions = false;
}

void InfoLayer::hideMoveMap()
{
	m_show_map = false;
	clearVertices();
	updateVertices();
}

void InfoLayer::showMoveMap()
{
	m_show_map = true;
}

void InfoLayer::syncMoveMap()
{
	for (int i = 0; i < m_map.size(); i++)
	{
		for (int j = 0; j < m_map[i].size(); j++)
		{
			int index = i + j*WIDTH;
			m_coords[index]->move_weight = m_map[i][j];
		}
	}
}

void InfoLayer::syncMoveMap(std::vector<std::vector<int>>& map)
{
	m_map = map;
}

void InfoLayer::resetMoveMap()
{
	for (auto c : m_coords) c->move_weight = 999;
}