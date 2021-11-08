#include "EnemyBoss.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

EnemyBoss::EnemyBoss(sf::RenderWindow* window)
{
	std::ifstream inputStream("./JSON/EnemyBoss.json");
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);

	m_textureName = document["texture"].ToString();
	m_score = document["score"].ToInt();
	m_movespeed = document["movespeed"].ToFloat();
	std::cout << m_movespeed << std::endl;
	m_health = document["health"].ToInt();

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setScale(document["scaleX"].ToFloat(), document["scaleY"].ToFloat());
	sprite->setPosition(0, -(window->getSize().y * 0.5));

	m_sprite = sprite;

	std::cout << "EnemyBoss created" << std::endl;
}

EnemyBoss::~EnemyBoss()
{
	std::cout << "EnemyBoss destroyed" << std::endl;
}

int EnemyBoss::DrawObject(sf::RenderWindow* window)
{
	// Loading image texture
	sf::Texture texture;

	// If this failed
	if (texture.loadFromFile(m_textureName) == false)
	{
		return 0;
	}

	m_sprite->setTexture(texture);
	m_sprite->move(0, m_movespeed);

	window->draw(*m_sprite);

	return 1;
}
