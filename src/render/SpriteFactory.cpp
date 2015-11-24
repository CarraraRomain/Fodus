#include "SpriteFactory.hpp"



SpriteFactory::SpriteFactory(Bootstrap* boot): m_boot(boot)
{
	LOG(DEBUG) << "Creating Sprite factory";
	m_sprites.reset(new rapidjson::Document());
	loadSpritesDoc("sprites_index");
	LOG(DEBUG) << "Factory ready";
}

SpriteFactory::~SpriteFactory()
{
}

AnimatedSprite* SpriteFactory::buildSprite(std::string key)
{
	rapidjson::Value& node = ((*m_sprites)["sprites"].HasMember(key.c_str())) ?
		(*m_sprites)["sprites"][key.c_str()] :
		(*m_sprites)["sprites"]["MLP"];
	AnimatedSprite* sp = new AnimatedSprite(sf::milliseconds(100), true, node.GetInt());
	return sp;
}

void SpriteFactory::loadSpritesDoc(const std::string& name)
{
	m_sprites = m_boot->getDocument(name);
}
