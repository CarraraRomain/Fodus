// config.h includes build & project config parameters
#include "config.h"

#include <iostream>
#include <fstream>
#include <sstream>

/* RapidJSON lib (fast header only lib) | Tested using v1.0.2
Lib is included in ../lib/rapidjson
URL : https://github.com/miloyip/rapidjson
*/
#include "../lib/rapidjson/document.h"

#include "../lib/rapidjson/writer.h"
#include "../lib/rapidjson/stringbuffer.h"
/* SFML Library | Tested using v2.3.2 / 2.3.1
URL : http://www.sfml-dev.org/
*/
#include <SFML/Graphics.hpp>


using namespace std;

int main(int argc, char* argv[]) {
	//FILE* pFile = fopen(, "rb");
    /* Code adapted from the SFML 2 "Window" example */
	cout << "Hello World" << endl;
    cout << FODUS_NAME << " version " << FODUS_VERSION_MAJOR << "." << FODUS_VERSION_MINOR << endl;

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


	std::stringstream ss;
	std::ifstream ifs;
	ifs.open("..\\res\\GFX\\tiles.json", std::ios::binary);
	if(ifs.is_open())
	{
		cout << "Good" << endl;
		ss << ifs.rdbuf(); // 1
		cout << "Done" << endl;
		if (d.Parse(ss.str().c_str()).HasParseError()) throw std::invalid_argument("JSON bad encoding");
		cout << ss.str();


		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);
		for (int i = 0; i < d["employees"].Size();i++)
		{
			cout << d["employees"][i]["firstName"].GetString() << endl;
		}
		
	}
	else
	{
		cout << "Bad" << endl;
	}
	
	

	ifs.close();

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