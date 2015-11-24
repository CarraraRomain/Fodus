#pragma once
#include "../global.hpp"
#include "../bootstrap/Bootstrap.hpp"
#include "AnimatedSprite.hpp"
class SpriteFactory
{
public:
	SpriteFactory(Bootstrap*);
	~SpriteFactory();
	std::shared_ptr<rapidjson::Document> getSpritesDoc();
	AnimatedSprite* buildSprite(std::string key);
	void loadSpritesDoc(const std::string&);
private:
	Bootstrap* m_boot;
	std::shared_ptr<rapidjson::Document> m_sprites;

};

