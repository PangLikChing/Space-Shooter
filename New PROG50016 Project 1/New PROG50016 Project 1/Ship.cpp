#include "Ship.h"
#include <iostream>

Ship::Ship()
{
	std::cout << "Ship created" << std::endl;
}

Ship::~Ship()
{
	std::cout << "Ship destroyed" << std::endl;
}

int& Ship::GetHealth()
{
	return m_health;
}

void Ship::SetHealth(int _health)
{
	m_health = _health;
}

std::vector<Projectile*>& Ship::GetProjectileList()
{
	return m_projectiles;
}

void Ship::PushProjectile(Projectile* _projectile)
{
	m_projectiles.push_back(_projectile);
}

void Ship::Shoot(sf::RenderWindow* window)
{
	std::cout << "Ship Shooting" << std::endl;
}
