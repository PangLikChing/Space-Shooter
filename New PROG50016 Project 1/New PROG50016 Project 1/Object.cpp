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

void Object::Move()
{
}

int Object::DrawObject(sf::RenderWindow* window)
{
	// This function doesn't work. It's just a template
	std::cout << "Drawing Object" << std::endl;
	return -1;
}