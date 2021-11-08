#include "Star.h"
#include <iostream>
#include "json.hpp"
#include <random>
#include <fstream>

Star::Star()
{

}

Star::Star(sf::RenderWindow* window)
{
	std::random_device ranDev;
	std::mt19937 rng(ranDev());
	std::uniform_int_distribution<std::mt19937::result_type> dist3(0, 2);

	if (dist3(rng) == 0)
	{
		std::ifstream inputStream("./JSON/StarBig.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON document = json::JSON::Load(str);

		m_textureName = document["texture"].ToString();
		m_isBig = document["isBig"].ToBool();
		m_movespeed = document["movespeed"].ToFloat();
	}
	else if (dist3(rng) == 1)
	{
		std::ifstream inputStream("./JSON/StarSmall.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON document = json::JSON::Load(str);

		m_textureName = document["texture"].ToString();
		m_isBig = document["isBig"].ToBool();
		m_movespeed = document["movespeed"].ToFloat();
	}
	else
	{
		std::ifstream inputStream("./JSON/Cloud.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON document = json::JSON::Load(str);

		m_textureName = document["texture"].ToString();
		m_isBig = document["isBig"].ToBool();
		m_movespeed = document["movespeed"].ToFloat();
	}

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setPosition((rand() % window->getSize().x * 0.8) + -(window->getSize().x * 0.4), -(window->getSize().y * 0.5));
	m_sprite = sprite;

	std::cout << "Star created" << std::endl;
}

Star::~Star()
{
	std::cout << "Star destroyed" << std::endl;
}

int Star::DrawObject(sf::RenderWindow* window)
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
