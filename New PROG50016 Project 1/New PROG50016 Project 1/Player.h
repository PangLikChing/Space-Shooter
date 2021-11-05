#ifndef PLAYER_H
#define PLAYER_H
#include "Ship.h"

class Player : public Ship
{
public:
	// Constructor / Destructor
	Player();

	~Player();

	float GetXMoveSpeed();
	float GetYMoveSpeed();

	void SetXMoveSpeed(float _newMovespeed);
	void SetYMoveSpeed(float _newMovespeed);

	// Methods
	int DrawObject(sf::RenderWindow* window) override;

	void Move() override;

	//void Shoot(sf::RenderWindow* window) override;

private:
	// Members
	float m_xMovespeed = 0.0f;
	float m_yMovespeed = 0.0f;
};

#endif // !PLAYER_H