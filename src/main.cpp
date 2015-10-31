#include "main.hpp"

/** Main entry point
Where all shall begin
*/
int main(int argc, char* argv[]) {
	// Logger config
	el::Configurations conf("../../res/config/logger.conf");
	el::Loggers::reconfigureAllLoggers(conf);

	// Launch Args
	// TODO to complete
	std::string type;
	if (argc > 1) type = argv[1];

	LOG(DEBUG) << "***";
	LOG(DEBUG) << "Fodus Started";
	LOG(DEBUG) << FODUS_NAME << " version " << FODUS_VERSION_MAJOR << "." << FODUS_VERSION_MINOR;

	std::shared_ptr<Bootstrap> boot;
	boot.reset(new Bootstrap);
	boot->start();

	std::shared_ptr<rapidjson::Document> tiles;
	tiles = boot->getDocument("tiles");
	std::cout << (*tiles)["header"]["name"].GetString() << std::endl;


	if (type == "editor") launch_editor(boot);
	else if (type == "game") launch_game(boot);
	else {
		do
		{
			std::cout << "> Launch game or level editor? (game/editor) ";
			std::cin >> type;
			if (type == "editor") launch_editor(boot);
			else if (type == "game") launch_game(boot);
		} while (type != "game" && type != "editor");
	}
    
    return 0;
}


void test_load_tiles(){
	std::vector<Tile> TVect;
	std::string key;
    int i=0;
	std::cout << "Testing loading Tiles from tiles.json..." << std::endl;
	TileFactory TFactory("../../res/GFX/tiles.json");
	std::cout << "Creating Tiles"<< std::endl;
    rapidjson::Value::ConstMemberIterator tiles = TFactory.getTilesDoc()->FindMember("tiles");
    for (rapidjson::Value::ConstMemberIterator itr = tiles->value.MemberBegin();
         itr != tiles->value.MemberEnd(); ++itr)
    {
        key = itr->name.GetString();
	    std::cout << "Found " << key << std::endl;
        TVect.push_back(*TFactory.buildTileForElt(key));
	    std::cout << "X:" << TVect[i].getX() << ", Y:" << TVect[i].getY() << std::endl;
        i++;

    }

}




void test_sfml() {
    // Creating dummy window
    sf::RenderWindow App(sf::VideoMode(SIZE*WIDTH,SIZE*HEIGHT), FODUS_NAME, sf::Style::Titlebar | sf::Style::Close);
	ElementList list;
    Scene scene("../../res/GFX/tiles.json");
	test_load_elt_list(&list);
	scene.update(list);
    while (App.isOpen()) {

        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }

        //App.clear(sf::Color::Black);
		
        App.draw(scene);
        //std::vector<sf::Sprite> FVect = test_load_level(App);

        
       // App.clear();

        App.display();
    }
}


/**
 * Launch the editor
 */
void launch_editor(std::shared_ptr<Bootstrap> boot)
{
	LOG(DEBUG) << "Launching Editor";
	bool nerr = true;
	std::string choice;
	std::string name;
	Editor editor(boot);
	std::cout << "Level Editor" << std::endl;
	do {
		while (choice != "yes"  && choice != "no")
		{
			std::cout << "\n======================\n";
			std::cout << "New level? (yes/no) ";
			std::cin >> choice;
		}
		// TODO Bootstrap will fetch all level names, awesome
		std::cout << "Level file name? ";
		std::cin >> name;
		editor.setFile(name);
		if (choice == "yes")
		{
			editor.new_level();
		}
		try
		{
			editor.load_level();
			nerr = true;
		}
		catch (const std::invalid_argument & e)
		{
			std::cerr << e.what();
			std::cerr << std::endl;
			nerr = false;
			choice = "";
		}

	} while (!nerr);
	std::cout << "Loading GUI..." << std::endl;
	editor.run();
}

/**
* Launch the game
*/
void launch_game(std::shared_ptr<Bootstrap> boot)
{
	LOG(DEBUG) << "Launching Game";
	std::cout << "Launching dat game..." << std::endl;
	// TODO Game class ( game.run() )
	test_sfml();
}


/**
* @deprecated
*/
std::vector<sf::Sprite> test_load_level(sf::RenderWindow& App){
        std::vector<sf::Sprite> SVect;
	std::cout << "Loading demo level JSON..." << std::endl;
        std::stringstream ss;
        rapidjson::Document d;
        std::ifstream ifs;
	std::string key;
        TileFactory TFactory("../../res/GFX/tiles.json");
        ifs.open("../../res/GFX/levels.json", std::ios::binary);
        if(ifs.is_open())
        {
            std::cout << "Good" << std::endl;
            ss << ifs.rdbuf(); // 1
            std::cout << "Done" << std::endl;
            if (d.Parse<0>(ss.str().c_str()).HasParseError()) throw std::invalid_argument("JSON bad encoding");
           // std::cout << ss.str();
        }
        else
        {
            std::cout << "Bad" << std::endl;
            exit(-1);
        }
        sf::Texture texture;
        if (!texture.loadFromFile("../../res/GFX/Tiles0_P1.png")) {
	        std::cout << "Erreur!" << std::endl;
        }

        //std::cout << d["header"].GetString();
        //cout << d["demo"][0][0]["key"].GetString();

        const rapidjson::Value& b = d["demo"];
        int posX = 0;
        for (rapidjson::SizeType i = 0; i < b.Size(); i++)
        {
            const rapidjson::Value& c = b[i];

           //cout << c[0]["key"].GetString();

            for (rapidjson::SizeType j = 0; j < c.Size(); j++)
            {
                // e : {"key", "repeat"}
                const rapidjson::Value& e = c[j];

                //cout << e["key"].GetString();
                for(int k=0; k < e["repeat"].GetInt();k++) {

                    sf::Sprite sprite;
                    Tile tile = *TFactory.buildTileForElt(e["key"].GetString());
                    sprite.setTexture(texture);
                    //sprite.setTextureRect(sf::IntRect(0, 22 * 32, 32, 32));
                    sprite.setTextureRect(sf::IntRect(tile.getY(), tile.getX(), 32, 32));
	                std::cout << e["key"].GetString() << ": X=" << tile.getX() << " Y=" << tile.getY() << std::endl;
                    sprite.move(sf::Vector2f(32 * posX, 32 * i));
                    SVect.push_back(sprite);
                    App.draw(sprite);
                    posX++;
                }

            }
            posX = 0;
        }

//       for (rapidjson::Value::ConstValueIterator itr = d["demo"].Begin();
//             itr != d["demo"].End(); ++itr)
//        {
//
//            for (rapidjson::Value::ConstValueIterator itr2 = itr.Begin();
//                 itr2 != itr.End(); ++itr2) {
//                cout << "Plop!";
//            }
//
//            cout << endl;
//            }


        ifs.close();

        return SVect;
    }


rapidjson::Document test_load_json_level()
{
	std::cout << "Loading demo level JSON..." << std::endl;
	std::stringstream ss;
	rapidjson::Document d;
	std::ifstream ifs;
	ifs.open("../../res/GFX/levels/test.json", std::ios::binary);
	if (ifs.is_open())
	{
		std::cout << "Good" << std::endl;
		ss << ifs.rdbuf(); // 1
		std::cout << "Done" << std::endl;
		if (d.Parse<0>(ss.str().c_str()).HasParseError()) throw std::invalid_argument("JSON bad encoding");
	}
	else
	{
		std::cout << "Bad" << std::endl;
		exit(-1);
	}
	ifs.close();
	return d;
}


void test_load_elt_list(ElementList* list)
{
	// loading a level from ../../res/GFX/level.json
	rapidjson::Document level = test_load_json_level();


	//std::cout << level["header"].GetString();
	//cout << level["level"][0][0][0..Depth]["key"].GetString();

	const rapidjson::Value& b = level["level"];
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

				list->push_back(elt);
			}
			posX++;
		}
		posX = 0;
	}


}
