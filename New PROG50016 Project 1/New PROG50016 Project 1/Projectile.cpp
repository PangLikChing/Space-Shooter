#include "Projectile.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

Projectile::Projectile()
{
	std::cout << "Projectile created" << std::endl;
}

Projectile::Projectile(sf::Vector2f _position)
{
	std::ifstream inputStream("./JSON/Projectile.json");
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);

	m_name = document["name"].ToString();
	m_textureName = document["texture"].ToString();
	m_movespeed = -(document["movespeed"].ToInt());

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setScale(document["scaleX"].ToFloat(), document["scaleY"].ToFloat());
	sprite->setPosition(_position);
	m_sprite = sprite;

	std::cout << "Projectile created" << std::endl;
}

Projectile::~Projectile()
{
	std::cout << "Projectile destroyed" << std::endl;
}

sf::Sprite* Projectile::GetSprite()
{
	return m_sprite;
}

int Projectile::DrawObject(sf::RenderWindow* window)
{
	// Loading image texture
	sf::Texture texture;
	// If this failed
	if (texture.loadFromFile(m_textureName) == false)
	{
		return 0;
	}

	m_sprite->setTexture(texture);
	m_sprite->move(0.0f, m_movespeed);

	window->draw(*m_sprite);
	return 1;
}