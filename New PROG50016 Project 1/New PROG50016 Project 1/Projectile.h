#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Object.h"

class Projectile : public Object
{
public:
	Projectile();

	Projectile(sf::Vector2f _position);

	~Projectile();

	int GetDamage();

	sf::Sprite* GetSprite();

	int DrawObject(sf::RenderWindow* window);

protected:
	int m_damage = 0;
};

#endif // !PROJECTILE_H