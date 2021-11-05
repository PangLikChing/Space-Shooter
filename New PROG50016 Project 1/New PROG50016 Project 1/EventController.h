#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H
#include "Player.h"
#include <SFML/Graphics.hpp>

class EventController
{
public:
	EventController();

	~EventController();

	void HandleEvents(sf::Event event, sf::RenderWindow* window, Player* player);
};

#endif // !EVENTCONTROLLER_H
