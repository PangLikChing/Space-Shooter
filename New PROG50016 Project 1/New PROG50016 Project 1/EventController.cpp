#include "EventController.h"
#include <iostream>

EventController::EventController()
{
	std::cout << "EventController created" << std::endl;
}

EventController::~EventController()
{
	std::cout << "EventController Destroyed" << std::endl;
}

void EventController::HandleEvents(sf::Event event, sf::RenderWindow* window, Player* player)
{
	switch (event.type)
	{
		// If the user close the window
	case sf::Event::Closed:
		window->close();
		delete window;
		window = nullptr;
		//return 0;
		break;

	case sf::Event::KeyPressed:
		// If W key is pressed
		if (event.key.code == sf::Keyboard::W)
		{
			player->SetYMoveSpeed(-5.0f);
			std::cout << "W" << std::endl;
			//std::cout << "control: " << event.key.control << std::endl;
			//std::cout << "alt: " << event.key.alt << std::endl;
			//std::cout << "shift: " << event.key.shift << std::endl;
			//std::cout << "system: " << event.key.system << std::endl;
		}
		// If A key is pressed
		if (event.key.code == sf::Keyboard::A)
		{
			player->SetXMoveSpeed(-5.0f);
			std::cout << "A" << std::endl;
		}
		// If S key is pressed
		if (event.key.code == sf::Keyboard::S)
		{
			player->SetYMoveSpeed(5.0f);
			std::cout << "S" << std::endl;
		}
		// If D key is pressed
		if (event.key.code == sf::Keyboard::D)
		{
			player->SetXMoveSpeed(5.0f);
			std::cout << "D" << std::endl;
		}
		break;

	case sf::Event::KeyReleased:
		// If W key is released
		if (event.key.code == sf::Keyboard::W)
		{
			player->SetYMoveSpeed(0.0f);
		}
		// If A key is released
		if (event.key.code == sf::Keyboard::A)
		{
			player->SetXMoveSpeed(0.0f);
		}
		// If S key is released
		if (event.key.code == sf::Keyboard::S)
		{
			player->SetYMoveSpeed(0.0f);
		}
		// If D key is released
		if (event.key.code == sf::Keyboard::D)
		{
			player->SetXMoveSpeed(0.0f);
		}
		// If spacebar is released
		if (event.key.code == sf::Keyboard::Space)
		{
			//player->Shoot(window);
		}
		// If esc is released
		if (event.key.code == sf::Keyboard::Escape)
		{
			// Quit game
			window->close();
			delete window;
			window = nullptr;
			//return 0;
			break;
		}
		break;

	case sf::Event::MouseButtonPressed:
		// If left mouse button is pressed
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			//player->Shoot(window);
			std::cout << "Left Mouse Button was Pressed" << std::endl;

			//auto mousePosition = sf::Mouse::getPosition(*window);
			//auto mousePositionToolWindow = window->mapPixelToCoords(mousePosition);
			//if (sprite.getGlobalBounds().contains(mousePositionToolWindow))
			//{
			//	std::cout << "Clicked the sprite" << std::endl;
			//}
		}
		break;

	default:
		break;
	}
}
