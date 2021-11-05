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
	std::string GetName();
	std::string GetTextureName();
	float GetMovespeed();
	sf::Sprite* GetSprite();

	void SetName(std::string _name);
	void SetTextureName(std::string _textureName);
	void SetMovespeed(float _movespeed);
	void SetSprite(sf::Sprite* _sprite);

	virtual void Move();
	virtual int DrawObject(sf::RenderWindow* window);

private:
	// Members
	std::string m_name = "";
	std::string m_textureName = "";
	float m_movespeed = 0.0f;
	sf::Sprite* m_sprite = nullptr;
};

#endif // !OBJECT_H