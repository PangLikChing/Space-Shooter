#include "Star.h"
#include <iostream>
#include <random>

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
		m_name = "StarBig";
		m_textureName = "starBig.png";
		m_isBig = true;
		m_movespeed = 0.5f;
	}
	else if (dist3(rng) == 1)
	{
		m_name = "StarSmall";
		m_textureName = "starSmall.png";
		m_isBig = false;
		m_movespeed = 0.5f;
	}
	else
	{
		m_name = "Cloud";
		m_textureName = "nebula.png";
		m_isBig = false;
		m_movespeed = 0.5f;
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
