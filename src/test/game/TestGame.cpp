#include "TestGame.hpp"
#include "../../state/Case.h"


TestGame::TestGame()
{

}

AnimatedSprite TestGame::m_animated_sprite(sf::seconds(0.2), true);;

TestGame::~TestGame()
{
}


rapidjson::Document TestGame::test_load_json_level()
{
	std::cout << "Loading demo level JSON..." << std::endl;
	std::stringstream ss;
	rapidjson::Document d;
	std::ifstream ifs;
	ifs.open("../../res/levels/test.json", std::ios::binary);
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


void TestGame::test_load_elt_list(ElementList* list, Bootstrap* boot)
{
	LOG(DEBUG) << "Loading Elt list";
	// loading a level from ../../res/GFX/level.json
	std::shared_ptr<rapidjson::Document> level;
	LOG(DEBUG) << "Get level test";
	level = boot->getLevel("test");
	LOG(DEBUG) << "Done";

	//std::cout << level["header"].GetString();
	//cout << level["level"][0][0][0..Depth]["key"].GetString();

	const rapidjson::Value& b = (*level)["level"];
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
				Case* ptr_case = new Case(rand());
				ptr_case->setKey(e[k]["key"].GetString());
				ptr_case->setX(posX);
				ptr_case->setY(i);
				ptr_case->setD(k);
				list->push_back(ptr_case);
			}
			posX++;
		}
		posX = 0;
	}

	LOG(DEBUG) << "Load OK";
}

