#include "Editor.hpp"
#include "../render/Scene.hpp"


using namespace std;

Editor::Editor()
{
	m_level = new rapidjson::Document;
	m_level->SetObject();
	m_list = new ElementList;
	m_editor_list = new ElementList;
}


Editor::~Editor()
{
	delete m_level;
	delete m_list;
	delete m_editor_list;
}

void Editor::load_level()
{
	std::stringstream ss;
	std::ifstream ifs;
	ifs.open("../../res/GFX/levels/" + m_file + ".json", std::ios::binary);
	if (ifs.is_open())
	{
		std::cout << "Good" << std::endl;
		ss << ifs.rdbuf(); // 1
		std::cout << "Done" << std::endl;
		if (m_level->Parse<0>(ss.str().c_str()).HasParseError()) throw std::invalid_argument("JSON bad encoding");
	}
	else throw std::invalid_argument("File Not Found");
	ifs.close();
}
/*
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
				Element* elt = new Element;
				elt->setKey(e[k]["key"].GetString());
				elt->setX(posX);
				elt->setY(i);
				elt->setD(k);

				m_list->push_back(elt);
			}
			posX++;
		}
		posX = 0;
	}

}

void Editor::load_tiles()
{
	string key;
	int i = 0;
	cout << "Loading Tiles from tiles.json..." << endl;
	TileFactory TFactory("../../res/GFX/tiles.json");
	rapidjson::Value::ConstMemberIterator tiles = TFactory.getTilesDoc()->FindMember("tiles");
	for (rapidjson::Value::ConstMemberIterator itr = tiles->value.MemberBegin();
	itr != tiles->value.MemberEnd(); ++itr)
	{
		Element* elt = new Element;
		elt->setKey(itr->name.GetString());
		elt->setX(i);
		elt->setY(0);
		elt->setD(0);
		m_editor_list->push_back(elt);
		i++;
	}

}

void Editor::run()
{
	sf::RenderWindow App(sf::VideoMode(SIZE*WIDTH, SIZE*HEIGHT), "Level", sf::Style::Titlebar | sf::Style::Close);
	App.setPosition(sf::Vector2i(0, 0));

	sf::RenderWindow AppEditor(sf::VideoMode(SIZE*WIDTH, SIZE*HEIGHT), "Tiles", sf::Style::Titlebar | sf::Style::Close);
	AppEditor.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width) / 2, 0));
	int start_x = 0, start_y = 0, end_x = 0, end_y = 0;
	Element* elt = nullptr;
	Scene scene("../../res/GFX/tiles.json");
	Scene scene_editor("../../res/GFX/tiles.json");
	sf::RectangleShape box;
	sf::Vector2f cur_pos;
	bool isSelecting = false;
	// Editor
	load_level();
	load_elts();
	load_tiles();
	scene.update(getList());
	scene_editor.update(getEditorList());
	while (App.isOpen()) {

		sf::Event event;
		// Main window event loop
		while (App.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				App.close();
				AppEditor.close();
				save();
				break;
			case sf::Event::MouseButtonPressed:
				if (elt)
				{
					start_x = event.mouseButton.x / SIZE;
					start_y = event.mouseButton.y / SIZE;
					std::cout << "Button was pressed" << std::endl;
					std::cout << "mouse x: " << start_x << std::endl;
					std::cout << "mouse y: " << start_y << std::endl;


					//editor->setElt(*elt, event.mouseButton.x / SIZE, event.mouseButton.y / SIZE, 0);
					//scene.update(editor->getList());
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (elt)
				{
					isSelecting = false;
					end_x = event.mouseButton.x / SIZE;
					end_y = event.mouseButton.y / SIZE;
					// Check boundaries
					end_x = (end_x >= WIDTH)  ?  WIDTH - 1 : end_x;
					end_x = (end_x <  0)	  ?			 0 : end_x;
					end_y = (end_y >= HEIGHT) ? HEIGHT - 1 : end_y;
					end_y = (end_y <  0)	  ?			 0 : end_y;
				
					std::cout << "Button was released" << std::endl;
					std::cout << "mouse x: " << end_x << std::endl;
					std::cout << "mouse y: " << end_y << std::endl;
					if (end_x < start_x)
					{
						int tmp = end_x;
						end_x = start_x;
						start_x = tmp;
					}
					if (end_y < start_y)
					{
						int tmp = end_y;
						end_y = start_y;
						start_y = tmp;
					}
					for (int k = start_y; k <= end_y; k++)
					{
						for (int i = start_x; i <= end_x; i++)
						{
							setElt(*elt, i, k);
						}
					}
					scene.update(getList());
				}
				break;
			case sf::Event::MouseMoved:
				if (elt && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					int draw_x = 0;
					int draw_y = 0;
					cur_pos.x = event.mouseMove.x - start_x*SIZE;
					cur_pos.y = event.mouseMove.y - start_y*SIZE;

					if (cur_pos.x >= 0) cur_pos.x = (int(cur_pos.x) / SIZE + 1) * SIZE;
					else cur_pos.x = (int(cur_pos.x) / SIZE - 2) * SIZE;
					if (cur_pos.y >= 0) cur_pos.y = (int(cur_pos.y) / SIZE + 1) * SIZE;
					else cur_pos.y = (int(cur_pos.y) / SIZE - 2) * SIZE;

					box.setSize(cur_pos);
					draw_x = (cur_pos.x < 0) ? start_x + 1 : start_x;
					draw_y = (cur_pos.y < 0) ? start_y + 1 : start_y;
					box.setPosition(draw_x*SIZE, draw_y*SIZE);
					box.setOutlineColor(sf::Color::Red);
					box.setFillColor(sf::Color::Transparent);
					box.setOutlineThickness(3);
					isSelecting = true;
				}
				break;

			}



		}
		// Editor window event loop
		while (AppEditor.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				App.close();
				AppEditor.close();
				save();
				break;
			case sf::Event::MouseButtonPressed:
				std::cout << "Button was pressed" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x / SIZE << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y / SIZE << std::endl;

				elt = getElt(event.mouseButton.x / SIZE, event.mouseButton.y / SIZE, 0);
				if (elt) cout << "Elt: " << elt->getKey() << endl;

				break;

			}
		}
		App.clear();
		AppEditor.clear();

		AppEditor.draw(scene_editor);
		App.draw(scene);

		if (isSelecting) App.draw(box);

		App.display();
		AppEditor.display();
	}

	cout << "Closing" << endl;
}

void Editor::setFile(std::string file)
{
	m_file = file;
}

ElementList* Editor::getList()
{
	return m_list;
}

ElementList* Editor::getEditorList()
{
	return m_editor_list;
}

void Editor::setElt(Element& elt, int x, int y, int depth)
{
	Element* search_elt;
	bool found = false;
	for (int i = 0; i < m_list->size(); i++)
	{
		search_elt = (*m_list)[i];
		if (search_elt->getX() == x && search_elt->getY() == y && search_elt->getD() == depth)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		search_elt->setKey(elt.getKey());
	}
	else
	{
		search_elt = new Element;
		*search_elt = elt;
		search_elt->setX(x);
		search_elt->setY(y);
		search_elt->setD(depth);
		m_list->push_back(search_elt);
	}

	(*m_level)["level"][y][x][depth]["key"].SetString(elt.getKey(), m_level->GetAllocator());
	


}


Element* Editor::getElt(int x, int y, int depth)
{

	for (int i = 0; i < m_editor_list->size(); i++)
	{
		Element* elt = (*m_editor_list)[i];
		if (elt->getX() == x && elt->getY() == y && elt->getD() == depth)
			return elt;
	}
	return nullptr;
}

void Editor::save()
{
	rapidjson::StringBuffer s;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> w(s);
	m_level->Accept(w);
	string json(s.GetString(), s.GetSize());
	ofstream of("../../res/GFX/levels/" + m_file + ".json");
	of << json;
	if (!of.good()) throw std::runtime_error("Can't write the JSON string to the file!");

}