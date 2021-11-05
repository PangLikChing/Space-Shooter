#include "Enemy.h"
#include <random>
#include <iostream>

Enemy::Enemy(sf::RenderWindow* window)
{
	std::random_device ranDev;
	std::mt19937 rng(ranDev());
	std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 1);
	m_isShip = dist2(rng);

	if (GetIsShip() == true)
	{
		Object::SetName("EnemyShip");
		Object::SetTextureName("enemyShip.png");
		Object::SetMovespeed(5.0f);
		Ship::SetHealth(1);
	}
	else
	{
		Object::SetName("EnemyUFO");
		Object::SetTextureName("enemyUFO.png");
		Object::SetMovespeed(2.0f);
		Ship::SetHealth(2);
	}

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setPosition((rand() % window->getSize().x * 0.8) + -(window->getSize().x * 0.4), -(window->getSize().y * 0.5));

	Object::SetSprite(sprite);

	std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy()
{
	std::cout << "Enemy destroyed" << std::endl;
}

bool Enemy::GetIsShip()
{
	return m_isShip;
}

int Enemy::DrawObject(sf::RenderWindow* window)
{
	// Loading image texture
	sf::Texture texture;

	// If this failed
	if (texture.loadFromFile(Object::GetTextureName()) == false)
	{
		return 0;
	}

	GetSprite()->setTexture(texture);
	GetSprite()->move(0, GetMovespeed());

	window->draw(*GetSprite());

	return 1;
}
