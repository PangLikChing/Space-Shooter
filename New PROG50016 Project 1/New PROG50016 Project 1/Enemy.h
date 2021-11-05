#ifndef ENEMY_H
#define ENEMY_H

#include "Ship.h"
class Enemy : public Ship
{
public:
	// Constructor / Destructor
	Enemy();

	Enemy(sf::RenderWindow* window);

	~Enemy();

	int& GetScore();

	int GetShootTimer();
	void SetShootTimer(int _shootTimer);

	// Methods
	int DrawObject(sf::RenderWindow* window) override;

	void Shoot(sf::RenderWindow* window);

protected:
	bool m_isShip = false;

	int m_shootTimer = 0;

	int m_score = 0;
};

#endif // !ENEMY_H