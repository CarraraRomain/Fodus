
#include "main.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	//FILE* pFile = fopen(, "rb");
    /* Code adapted from the SFML 2 "Window" example */
	cout << "Hello World" << endl;
    cout << FODUS_NAME << " version " << FODUS_VERSION_MAJOR << "." << FODUS_VERSION_MINOR << endl;

    char *path=NULL;
    size_t size;
    path=getcwd(path,size);
    cout<<"\n current Path"<<path<<endl;
	// RapidJSON test
	// 1. Parse a JSON string into DOM.
	const char* json = "{\"project\":\"" FODUS_NAME "\",\"version\":1}";
	rapidjson::Document d;
	d.Parse(json);
	// 2. Modify it by DOM.
	rapidjson::Value& s = d["version"];
	s.SetInt(s.GetInt() + 1);
	// 3. Stringify the DOM
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	cout << buffer.GetString() << endl;

	test_load_tiles();
    test_sfml();
    return 0;
}


void test_load_tiles(){
    vector<Tile> TVect;
    string key;
    int i=0;
	cout << "Testing loading Tiles from tiles.json..." << endl;
	TileFactory TFactory("../../res/GFX/tiles.json");
    cout << "Creating Tiles"<<endl;

    for (rapidjson::Value::ConstMemberIterator itr = TFactory.getTilesDoc()->MemberBegin();
         itr != TFactory.getTilesDoc()->MemberEnd(); ++itr)
    {
        key = itr->name.GetString();
        cout << "Found " << key << endl;
        TVect.push_back(*TFactory.buildTileForElt(key));
        cout << "X:" << TVect[i].getX() << ", Y:" << TVect[i].getY() << endl;
        i++;

    }

}




void test_sfml() {
    // Creating dummy window
    sf::RenderWindow App(sf::VideoMode(800, 600), FODUS_NAME);
    sf::Texture texture;
    sf::Sprite sprite;
    if (!texture.loadFromFile("../../res/GFX/Tiles0_P1.png")) {
        cout << "Erreur!" << endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 22 * 32, 32, 32));

    while (App.isOpen()) {

        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }

        App.clear(sf::Color::Black);


        std::vector<sf::Sprite> FVect = test_load_level(App);
        App.draw(sprite);
        /*// Dummy blue rect shape
        sf::RectangleShape shape(sf::Vector2f(100,200));
        shape.setFillColor(sf::Color(42, 50, 250));
        shape.setPosition(100,100);
        App.draw(shape);
        // Basic transform
        sf::Transform t;
        t.translate(10, 100);
        t.rotate(-45);
        App.clear();
        App.draw(shape, t);*/


        App.display();
    }
}

    std::vector<sf::Sprite> test_load_level(sf::RenderWindow& App){
        std::vector<sf::Sprite> SVect;
        cout << "Loading demo level JSON..." << endl;
        std::stringstream ss;
        rapidjson::Document d;
        std::ifstream ifs;
        string key;
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
            cout << "Erreur!" << endl;
        }

        //std::cout << d["header"].GetString();
        //cout << d["demo"][0][0]["key"].GetString();

        const rapidjson::Value& b = d["demo"];

        for (rapidjson::SizeType i = 0; i < b.Size(); i++)
        {
            const rapidjson::Value& c = b[i];

           //cout << c[0]["key"].GetString();

            for (rapidjson::SizeType j = 0; j < c.Size(); j++)
            {
                const rapidjson::Value& e = c[j];

                //cout << e["key"].GetString();
                sf::Sprite sprite;
                Tile tile = *TFactory.buildTileForElt(e["key"].GetString());
                sprite.setTexture(texture);
                //sprite.setTextureRect(sf::IntRect(0, 22 * 32, 32, 32));
                sprite.setTextureRect(sf::IntRect(tile.getY(), tile.getX(), 32, 32));
                cout << e["key"].GetString() << ": X=" << tile.getX() << " Y=" << tile.getY()<<endl;
                sprite.move(sf::Vector2f(32*j, 32*i));
                SVect.push_back(sprite);
                App.draw(sprite);


            }
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
