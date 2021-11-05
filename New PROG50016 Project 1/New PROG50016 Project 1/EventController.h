#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"
#include <vector>
#include <SFML/Graphics.hpp>

class EventController
{
public:
	EventController();

	~EventController();

	void HandleEvents(sf::Event event, sf::RenderWindow* window, Player* player, std::vector<Enemy*>& enemies, std::vector<Asteroid*>& asteroids);
};

#endif // !EVENTCONTROLLER_H
