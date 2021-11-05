#ifndef ENEMY_H
#define ENEMY_H

#include "Ship.h"
class Enemy : public Ship
{
public:
	// Constructor / Destructor
	Enemy(sf::RenderWindow* window);

	~Enemy();

	bool GetIsShip();

	// Methods
	int DrawObject(sf::RenderWindow* window) override;

private:
	bool m_isShip = false;
};

#endif // !ENEMY_H