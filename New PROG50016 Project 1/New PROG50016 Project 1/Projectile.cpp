#include "Projectile.h"
#include <iostream>

Projectile::Projectile()
{
	std::cout << "Projectile created" << std::endl;
}

Projectile::Projectile(sf::Vector2f _position)
{
	m_name = "Projectile";
	m_textureName = "laserRed.png";
	m_movespeed = -10.0f;

	sf::Sprite* sprite = new sf::Sprite;
	sprite->setPosition(_position);
	m_sprite = sprite;

	std::cout << "Projectile created" << std::endl;
}

Projectile::~Projectile()
{
	std::cout << "Projectile destroyed" << std::endl;
}

sf::Sprite* Projectile::GetSprite()
{
	return m_sprite;
}

int Projectile::DrawObject(sf::RenderWindow* window)
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