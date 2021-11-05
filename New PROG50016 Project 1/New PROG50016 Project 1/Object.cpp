#include "Object.h"
#include <iostream>

Object::Object()
{
	std::cout << "Object created" << std::endl;
}

Object::~Object()
{
	std::cout << "Object destroyed" << std::endl;
}

std::string Object::GetName()
{
	return m_name;
}

std::string Object::GetTextureName()
{
	return m_textureName;
}

float Object::GetMovespeed()
{
	return m_movespeed;
}

sf::Sprite* Object::GetSprite()
{
	return m_sprite;
}

void Object::SetName(std::string _name)
{
	m_name = _name;
}

void Object::SetTextureName(std::string _textureName)
{
	m_textureName = _textureName;
}

void Object::SetMovespeed(float _movespeed)
{
	m_movespeed = _movespeed;
}

void Object::SetSprite(sf::Sprite* _sprite)
{
	m_sprite = _sprite;
}

void Object::Move()
{
}

int Object::DrawObject(sf::RenderWindow* window)
{
	// This function doesn't work. It's just a template
	std::cout << "Drawing Object" << std::endl;
	return -1;
}