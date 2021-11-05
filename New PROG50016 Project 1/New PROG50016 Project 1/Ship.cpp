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
