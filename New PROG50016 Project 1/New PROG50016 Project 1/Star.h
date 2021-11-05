#ifndef STAR_H
#define STAR_H

#include "Object.h"
class Star : public Object
{
public:
	// Constructor / Destructor
	Star();

	Star(sf::RenderWindow* window);

	~Star();

	// Methods
	int DrawObject(sf::RenderWindow* window) override;

private:
	// Member
	bool m_isBig = false;
};
#endif // !STAR_H