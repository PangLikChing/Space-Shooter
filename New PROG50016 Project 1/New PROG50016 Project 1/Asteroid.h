#ifndef ASTEROID_H
#define ASTEROID_H
#include "Object.h"

class Asteroid : public Object
{
public:
	// Constructor / Destructor
	Asteroid(sf::RenderWindow* window);

	~Asteroid();

	// Methods
	int DrawObject(sf::RenderWindow* window) override;

private:
	// Member
	int m_health = 0;

	bool m_isBig = false;
};

#endif // !ASTEROID_H