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

	// Methods
	int GetHealth();
	std::vector<Projectile*> GetProjectileList();

	void SetHealth(int _health);
	void PushProjectile(Projectile* _projectile);

	virtual void Shoot(sf::RenderWindow* window);

private:
	// Members
	int m_health = 0;
	std::vector<Projectile*> m_projectiles;
};

#endif // !SHIP_H