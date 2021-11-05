#ifndef ASTEROID_H
#define ASTEROID_H
#include "Star.h"

class Asteroid : public Star
{
public:
	// Constructor / Destructor
	Asteroid(sf::RenderWindow* window);

	~Asteroid();

	int& GetHealth();
	void SetHealth(int _health);

	// Methods
	int DrawObject(sf::RenderWindow* window) override;

private:
	// Member
	int m_health = 0;

	bool m_isBig = false;
};

#endif // !ASTEROID_H