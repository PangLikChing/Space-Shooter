#include "Player.h"
//#include "Projectile.h"
#include <iostream>

Player::Player()
{
	// Loading image texture
	m_name = "Player";
	m_textureName = "Player.png";
	m_health = 3;

	sf::Sprite* sprite = new sf::Sprite;

	m_sprite = sprite;

	std::cout << "Player created" << std::endl;
	std::cout << "Player has " << m_health << " Health" << std::endl;
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

float Player::GetXMoveSpeed()
{
	return m_xMovespeed;
}

float Player::GetYMoveSpeed()
{
	return m_yMovespeed;
}

void Player::SetXMoveSpeed(float _newMovespeed)
{
	m_xMovespeed = _newMovespeed;
}

void Player::SetYMoveSpeed(float _newMovespeed)
{
	m_yMovespeed = _newMovespeed;
}

int Player::DrawObject(sf::RenderWindow* window)
{
	sf::Texture texture;
	// If this failed
	if (texture.loadFromFile(m_textureName) == false)
	{
		return 0;
	}

	m_sprite->setTexture(texture);
	m_sprite->move(m_xMovespeed, m_yMovespeed);

	window->draw(*m_sprite);
	return 1;
}

void Player::Shoot(sf::RenderWindow* window)
{
	Projectile* projectile = new Projectile(m_sprite->getPosition());
	PushProjectile(projectile);
	
	// Delete the useless projectiles on shoot
	// Can also do a pass by reference for loop in main. But looping every frame doesn't seem good to me
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles[i]->GetSprite()->getPosition().y < -(window->getSize().y * 0.5))
		{
			delete(m_projectiles[i]);
			m_projectiles[i] = nullptr;
			m_projectiles.erase(m_projectiles.begin() + i);
		}
	}

	std::cout << "Player Shooting" << std::endl;
}