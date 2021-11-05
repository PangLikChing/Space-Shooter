#include "Enemy.h"
#include "EnemyProjectile.h"
#include <random>
#include <iostream>

Enemy::Enemy()
{

}

Enemy::Enemy(sf::RenderWindow* window)
{
	std::random_device ranDev;
	std::mt19937 rng(ranDev());
	std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 1);
	m_isShip = dist2(rng);

	if (m_isShip == true)
	{
		m_name = "EnemyShip";
		m_textureName = "enemyShip.png";
		m_score = 1;
		m_movespeed = 5.0f;
		m_health = 1;
	}
	else
	{
		m_name = "EnemyUFO";
		m_textureName = "enemyUFO.png";
		m_score = 3;
		m_movespeed = 2.0f;
		m_health = 2;
	}

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setPosition((rand() % window->getSize().x * 0.8) + -(window->getSize().x * 0.4), -(window->getSize().y * 0.5));

	m_sprite = sprite;

	std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy()
{
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		delete(m_projectiles[i]);
	}
	std::cout << "Enemy destroyed" << std::endl;
}

int& Enemy::GetScore()
{
	return m_score;
}

int Enemy::GetShootTimer()
{
	return m_shootTimer;
}

void Enemy::SetShootTimer(int _shootTimer)
{
	m_shootTimer = _shootTimer;
}

int Enemy::DrawObject(sf::RenderWindow* window)
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

void Enemy::Shoot(sf::RenderWindow* window)
{
	EnemyProjectile* projectile = new EnemyProjectile(m_sprite->getPosition());
	PushProjectile(projectile);
	// Delete the useless projectiles on shoot
	// Can also do a pass by reference for loop in main. But looping every frame doesn't seem good to me
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles[i]->GetSprite()->getPosition().y > (window->getSize().y * 0.5))
		{
			delete(m_projectiles[i]);
			m_projectiles[i] = nullptr;
			m_projectiles.erase(m_projectiles.begin() + i);
		}
	}

	std::cout << "Enemy Shooting" << std::endl;
}
