#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include "Enemy.h"
class EnemyBoss : public Enemy
{
public:
	EnemyBoss(sf::RenderWindow* window);

	~EnemyBoss();

	// Methods
	int DrawObject(sf::RenderWindow* window) override;
};

#endif // !ENEMYBOSS_H