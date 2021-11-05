#ifndef ENEMY_H
#define ENEMY_H

#include "Ship.h"
class Enemy : public Ship
{
public:
	// Constructor / Destructor
	Enemy(sf::RenderWindow* window);

	~Enemy();

	int GetShootTimer();
	void SetShootTimer(int _shootTimer);

	// Methods
	int DrawObject(sf::RenderWindow* window) override;

	void Shoot(sf::RenderWindow* window);

private:
	bool m_isShip = false;

	int m_shootTimer = 0;
};

#endif // !ENEMY_H