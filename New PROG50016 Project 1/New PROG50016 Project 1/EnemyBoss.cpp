#include "EnemyBoss.h"
#include <iostream>

EnemyBoss::EnemyBoss(sf::RenderWindow* window)
{
	m_name = "EnemyBoss";
	m_textureName = "enemyUFO.png";
	m_score = 100;
	m_movespeed = 0.5f;
	m_health = 10;

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setScale(4.0f, 4.0f);
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
