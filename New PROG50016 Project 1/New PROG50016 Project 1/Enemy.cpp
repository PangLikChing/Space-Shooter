#include "Enemy.h"
#include "EnemyProjectile.h"
#include "json.hpp"
#include <random>
#include <iostream>
#include <fstream>

Enemy::Enemy()
{

}

Enemy::Enemy(sf::RenderWindow* window)
{
	std::random_device ranDev;
	std::mt19937 rng(ranDev());
	std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 1);
	m_isShip = dist2(rng);

	sf::Sprite* sprite = new sf::Sprite;

	if (m_isShip == true)
	{
		std::ifstream inputStream("./JSON/EnemyShip.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON document = json::JSON::Load(str);

		m_name = document["name"].ToString();
		m_textureName = document["texture"].ToString();
		m_score = document["score"].ToInt();
		m_movespeed = document["movespeed"].ToFloat();
		m_health = document["health"].ToInt();
		sprite->setScale(document["scaleX"].ToFloat(), document["scaleY"].ToFloat());
	}
	else
	{
		std::ifstream inputStream("./JSON/EnemyUFO.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON document = json::JSON::Load(str);

		m_name = document["name"].ToString();
		m_textureName = document["texture"].ToString();
		m_score = document["score"].ToInt();
		m_movespeed = document["movespeed"].ToFloat();
		m_health = document["health"].ToInt();
		sprite->setScale(document["scaleX"].ToFloat(), document["scaleY"].ToFloat());
	}

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
