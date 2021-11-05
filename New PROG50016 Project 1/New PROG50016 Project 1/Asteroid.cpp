#include "Asteroid.h"
#include <iostream>
#include <random>

Asteroid::Asteroid(sf::RenderWindow* window)
{

	std::random_device ranDev;
	std::mt19937 rng(ranDev());
	std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 1);
	m_isBig = dist2(rng);

	if (m_isBig == true)
	{
		m_name = "AsteroidBig";
		m_textureName = "meteorBig.png";
		m_movespeed = 0.5f;
		m_health = 3;
	}
	else
	{
		m_name = "AsteroidSmall";
		m_textureName = "meteorSmall.png";
		m_movespeed = 0.5f;
		m_health = 1;
	}

	sf::Sprite* sprite = new sf::Sprite;
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