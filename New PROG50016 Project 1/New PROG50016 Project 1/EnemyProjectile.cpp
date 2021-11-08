#include "EnemyProjectile.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

EnemyProjectile::EnemyProjectile(sf::Vector2f _position)
{
	std::ifstream inputStream("./JSON/EnemyProjectile.json");
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);

	m_name = document["name"].ToString();
	m_textureName = document["texture"].ToString();
	m_movespeed = document["movespeed"].ToFloat();

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setScale(document["scaleX"].ToFloat(), document["scaleY"].ToFloat());
	sprite->setPosition(_position);
	m_sprite = sprite;

	std::cout << "EnemyProjectile created" << std::endl;
}

EnemyProjectile::~EnemyProjectile()
{
	std::cout << "EnemyProjectile destroyed" << std::endl;
}
