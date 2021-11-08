#include "Asteroid.h"
#include <iostream>
#include "json.hpp"
#include <random>
#include <fstream>

Asteroid::Asteroid(sf::RenderWindow* window)
{
	std::random_device ranDev;
	std::mt19937 rng(ranDev());
	std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 1);
	m_isBig = dist2(rng);

	sf::Sprite* sprite = new sf::Sprite;

	if (m_isBig == true)
	{
		std::ifstream inputStream("./JSON/AsteroidBig.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON document = json::JSON::Load(str);

		m_name = document["name"].ToString();
		m_textureName = document["texture"].ToString();
		m_movespeed = document["movespeed"].ToFloat();
		m_health = document["health"].ToInt();
		sprite->setScale(document["scaleX"].ToFloat(), document["scaleY"].ToFloat());
	}
	else
	{
		std::ifstream inputStream("./JSON/AsteroidSmall.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON document = json::JSON::Load(str);

		m_name = document["name"].ToString();
		m_textureName = document["texture"].ToString();
		m_movespeed = document["movespeed"].ToFloat();
		m_health = document["health"].ToInt();
		sprite->setScale(document["scaleX"].ToFloat(), document["scaleY"].ToFloat());
	}

	sprite->setPosition((rand() % window->getSize().x * 0.8) + -(window->getSize().x * 0.4), -(window->getSize().y * 0.5));
	m_sprite = sprite;

	std::cout << "Asteroid created" << std::endl;
}

Asteroid::~Asteroid()
{
	std::cout << "Asteroid destroyed" << std::endl;
}

int& Asteroid::GetHealth()
{
	return m_health;
}

void Asteroid::SetHealth(int _health)
{
	m_health = _health;
}

int Asteroid::DrawObject(sf::RenderWindow* window)
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