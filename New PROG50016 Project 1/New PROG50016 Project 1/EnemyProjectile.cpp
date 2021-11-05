#include "EnemyProjectile.h"
#include <iostream>

EnemyProjectile::EnemyProjectile(sf::Vector2f _position)
{
	m_name = "EnemyProjectile";
	m_textureName = "laserGreen.png";
	m_movespeed = 10.0f;

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setPosition(_position);
	m_sprite = sprite;

	std::cout << "EnemyProjectile created" << std::endl;
}

EnemyProjectile::~EnemyProjectile()
{
	std::cout << "EnemyProjectile destroyed" << std::endl;
}
