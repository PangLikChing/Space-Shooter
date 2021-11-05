#ifndef SHIP_H
#define SHIP_H
#include "Object.h"
#include "Projectile.h"
#include <vector>

class Ship : public Object
{
public:
	Ship();

	~Ship();

	std::vector<Projectile*>& GetProjectileList();

	// Methods
	void PushProjectile(Projectile* _projectile);

	virtual void Shoot(sf::RenderWindow* window);

protected:
	// Members
	int m_health = 0;
	std::vector<Projectile*> m_projectiles;
};

#endif // !SHIP_H