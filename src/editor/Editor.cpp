#include "Editor.hpp"



using namespace std;

Editor::Editor(Bootstrap* boot)
{
	m_boot = boot;
}


Editor::~Editor()
{
}
/**
 * Init GUI vars
 */
void Editor::load_gui()
{
	LOG(DEBUG) << "Loading GUI";
	m_level_scene.reset(new Scene(m_boot));
	m_editor_scene.reset(new Scene(m_boot));
	m_level_window.reset(new sf::RenderWindow(sf::VideoMode(SIZE*WIDTH,
		SIZE*HEIGHT), "Level", sf::Style::Titlebar | sf::Style::Close));
	m_level_window->setPosition(sf::Vector2i(0, 0));

	m_editor_window.reset(new sf::RenderWindow(sf::VideoMode(SIZE*WIDTH,
		SIZE*HEIGHT), "Tiles", sf::Style::Titlebar | sf::Style::Close));
	m_editor_window->setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width) / 2, 0));
	m_box.reset(new SelectBox());

}

/**
 * JSON level loader
 */
void Editor::load_level()
{
	LOG(DEBUG) << "Get level " << m_file;
	m_level.reset(new rapidjson::Document);
	m_level->SetObject();
	m_level = m_boot->getLevel(m_file);
	LOG(DEBUG) << "Done";
}
/**
 * JSON Template V2
 */
void Editor::new_level()
{
	rapidjson::StringBuffer s;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> w(s);

	w.StartObject();
	// Header
	w.String("header");
	w.StartObject();
	w.String("version");
	w.String("0.0");
	w.String("name");
	w.String("My Little Level");
	w.String("desc");
	w.String("Misc");
	w.EndObject();
	// Level
	w.String("level");
	w.StartArray();
	// Each row
	for (int i = 0; i < HEIGHT; i++)
	{
		w.StartArray();
		// Each cell
		for (int k = 0; k < WIDTH; k++)
		{
			// Has 2 layers
			w.StartArray();
			w.StartObject();
			w.String("key");
			w.String("UNDEFINED");
			w.EndObject();
			w.StartObject();
			w.String("key");
			w.String("VOID");
			w.EndObject();
			w.EndArray();
		}
		w.EndArray();
	}
	w.EndArray();
	w.EndObject();
	string json(s.GetString());
	ofstream of("../../res/GFX/levels/" + m_file + ".json");
	of << json;
	if (!of.good()) throw std::runtime_error("Can't write the JSON string to the file!");

}

void Editor::load_elts()
{
	m_level_list.reset(new ElementList());
	//std::cout << level["header"].GetString();
	//cout << level["level"][0][0][0..Depth]["key"].GetString();

	const rapidjson::Value& b = (*m_level)["level"];
	int posX = 0;
	for (rapidjson::SizeType i = 0; i < b.Size(); i++)
	{
		const rapidjson::Value& c = b[i];
		//cout << c[0][0..Depth]["key"].GetString();

		for (rapidjson::SizeType j = 0; j < c.Size(); j++)
		{
			// X = j | Y = i
			// e : [0..Depth]["key"]
			const rapidjson::Value& e = c[j];

			for (rapidjson::SizeType k = 0; k < e.Size(); k++) {
				Element elt = Element();
				elt.setKey(e[k]["key"].GetString());
				elt.setX(posX);
				elt.setY(i);
				elt.setD(k);

				m_level_list->push_back(elt);
			}
			posX++;
		}
		posX = 0;
	}

}

void Editor::load_tiles()
{
	m_editor_list.reset(new ElementList());
	string key;
	int i = 0;
	TileFactory TFactory(m_boot);
	rapidjson::Value::ConstMemberIterator tiles = TFactory.getTilesDoc()->FindMember("tiles");
	for (rapidjson::Value::ConstMemberIterator itr = tiles->value.MemberBegin();
	itr != tiles->value.MemberEnd(); ++itr)
	{
		Element elt = Element();
		elt.setKey(itr->name.GetString());
		elt.setX(i%WIDTH);
		LOG(DEBUG) << "i: " << i << ", Y: " << i / WIDTH;
		elt.setY(i/WIDTH);
		elt.setD(0);
		m_editor_list->push_back(elt);
		i++;
	}

}

/**
 * Loading
 */
void Editor::load()
{
	load_gui();
	load_level();
	load_elts();
	load_tiles();
}
/**
 * Main loop
 */
void Editor::run()
{
	LOG(DEBUG) << "Editor is running";
	load();
	
	// Editor
	
	m_level_scene->update(*m_level_list);
	m_editor_scene->update(*m_editor_list);
	while (m_level_window->isOpen()) {

		level_event_loop();
		editor_event_loop();
	
		m_level_window->clear();
		m_editor_window->clear();

		m_editor_window->draw(*m_editor_scene);
		m_level_window->draw(*m_level_scene);
		
		m_level_window->draw(*m_box);

		m_level_window->display();
		m_editor_window->display();
	}

	LOG(DEBUG) << "Editor ended";
}

void Editor::setFile(std::string file)
{
	m_file = file;
}



void Editor::setElt(Element elt, int x, int y, int depth)
{
	
	bool found = false;
	for (int i = 0; i < int(m_level_list->size()); i++)
	{
	
		if ((*m_level_list)[i]->getX() == x && (*m_level_list)[i]->getY() == y && (*m_level_list)[i]->getD() == depth)
		{
			(*m_level_list)[i]->setKey(elt.getKey());
			found = true;
			break;
		}
	}
	if (!found)
	{
		Element el = Element();
		el.setKey(elt.getKey());
		el.setX(x);
		el.setY(y);
		el.setD(depth);
		m_editor_list->push_back(el);
	}

	(*m_level)["level"][y][x][depth]["key"].SetString(elt.getKey(), m_level->GetAllocator());
	


}

Element Editor::getElt(int x, int y, int depth)
{

	for (int i = 0; i < int(m_editor_list->size()); i++)
	{
		Element elt = *(*m_editor_list)[i];
		if (elt.getX() == x && elt.getY() == y && elt.getD() == depth)
			return elt;
	}
	throw std::domain_error("Bad Coord");
}

void Editor::save()
{
	rapidjson::StringBuffer s;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> w(s);
	m_level->Accept(w);
	string json(s.GetString(), s.GetSize());
	ofstream of("../../res/levels/" + m_file + ".json");
	of << json;
	if (!of.good()) throw std::runtime_error("Can't write the JSON string to the file!");

}

void Editor::level_event_loop()
{
	sf::Event event;
	// Main window event loop
	while (m_level_window->pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			m_level_window->close();
			m_editor_window->close();
			save();
			break;
		case sf::Event::MouseButtonPressed:
			if (m_selected_elt)
			{
				m_box->setStart(sf::Vector2i(event.mouseButton.x / SIZE,
					event.mouseButton.y / SIZE));
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (m_selected_elt)
			{
				m_box->inactive();
				m_box->setEnd(sf::Vector2i(event.mouseButton.x / SIZE,
					event.mouseButton.y / SIZE));



				for (int k = m_box->getStart().y; k <= m_box->getEnd().y; k++)
				{
					for (int i = m_box->getStart().x; i <= m_box->getEnd().x; i++)
					{
						setElt(*m_selected_elt, i, k);
					}
				}
				m_level_scene->update(*m_level_list);
			}
			break;
		case sf::Event::MouseMoved:
			if (m_selected_elt && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_box->setCurrent(sf::Vector2i(event.mouseMove.x / SIZE,
					event.mouseMove.y / SIZE));
				m_box->setBox();
				m_box->active();
			}
			break;

		}



	}
}

void Editor::editor_event_loop()
{
	sf::Event event;
	// Editor window event loop
	while (m_editor_window->pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			m_level_window->close();
			m_editor_window->close();
			save();
			break;
		case sf::Event::MouseButtonPressed:
			std::cout << "Button was pressed" << std::endl;
			std::cout << "mouse x: " << event.mouseButton.x / SIZE << std::endl;
			std::cout << "mouse y: " << event.mouseButton.y / SIZE << std::endl;
			try{
				m_selected_elt.reset(new Element(getElt(event.mouseButton.x / SIZE,
														event.mouseButton.y / SIZE, 0)));
				LOG(INFO) << "Elt: " << m_selected_elt->getKey();
			}catch (const std::domain_error& e){
				LOG(WARNING) << "No Elt here";
				}
			break;

		}
	}
}