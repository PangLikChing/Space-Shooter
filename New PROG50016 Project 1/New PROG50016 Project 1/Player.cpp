#include "Player.h"
//#include "Projectile.h"
#include <iostream>

Player::Player()
{
	// Loading image texture
	Object::SetName("Player");
	Object::SetTextureName("Player.png");
	Ship::SetHealth(3);

	sf::Sprite* sprite = new sf::Sprite;

	Object::SetSprite(sprite);

	std::cout << "Player created" << std::endl;
	//std::cout << "Player has " << GetHealth() << " Health" << std::endl;
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
	if (texture.loadFromFile(Object::GetTextureName()) == false)
	{
		return 0;
	}

	GetSprite()->setTexture(texture);
	GetSprite()->move(m_xMovespeed, m_yMovespeed);

	window->draw(*GetSprite());
	return 1;
}

void Player::Move()
{
	//SetPosition(sf::Vector2f(GetPosition().x + m_xMovespeed, GetPosition().y + m_yMovespeed));
}

//void Player::Shoot(sf::RenderWindow* window)
//{
//	Projectile* projectile = new Projectile();
//	PushProjectile(projectile);
//	projectile->DrawObject(window, GetSprite()->getPosition());
//
//	std::cout << "Player Shooting" << std::endl;
//}