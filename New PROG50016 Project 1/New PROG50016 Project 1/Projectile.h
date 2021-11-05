#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Object.h"

class Projectile : public Object
{
public:
	Projectile();

	Projectile(sf::Vector2f _position);

	~Projectile();

	sf::Sprite* GetSprite();

	int DrawObject(sf::RenderWindow* window);
};

#endif // !PROJECTILE_H