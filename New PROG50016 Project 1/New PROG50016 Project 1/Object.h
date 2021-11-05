#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <SFML\Graphics.hpp>

class Object
{
public:
	// Constructor / Destructor
	Object();

	~Object();

	// Methods
	virtual void Move();
	virtual int DrawObject(sf::RenderWindow* window);

protected:
	// Members
	std::string m_name = "";
	std::string m_textureName = "";
	float m_movespeed = 0.0f;
	sf::Sprite* m_sprite = nullptr;
};

#endif // !OBJECT_H