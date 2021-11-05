#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H
#include "Projectile.h"

class EnemyProjectile : public Projectile
{
public:
	EnemyProjectile(sf::Vector2f _position);

	~EnemyProjectile();
};

#endif // !ENEMYPROJECTILE_H