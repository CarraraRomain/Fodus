
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

void test_sfml(){
	// Creating dummy window
	sf::RenderWindow App(sf::VideoMode(800, 600), FODUS_NAME);

	while (App.isOpen()) {

		sf::Event Event;
		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();
		}

		App.clear(sf::Color::Black);

		// Dummy blue rect shape
		sf::RectangleShape shape(sf::Vector2f(100,200));
		shape.setFillColor(sf::Color(42, 50, 250));
		shape.setPosition(100,100);
		App.draw(shape);
		// Basic transform
		sf::Transform t;
		t.translate(10, 100);
		t.rotate(-45);
		App.clear();
		App.draw(shape, t);


		App.display();
}
}