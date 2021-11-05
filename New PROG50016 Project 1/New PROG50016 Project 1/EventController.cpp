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

// Should do the delete events on the Game Manager instead. See if I have time to implement it
void EventController::HandleEvents(sf::Event event, sf::RenderWindow* window, Player* player, std::vector<Enemy*>& enemies, std::vector<Asteroid*>& asteroids, std::vector<Star*>& stars)
{
	switch (event.type)
	{
		// If the user close the window
	case sf::Event::Closed:
		window->close();
		delete player;
		player = nullptr;
		for (int i = 0; i < enemies.size(); i++)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		for (int i = 0; i < asteroids.size(); i++)
		{
			delete asteroids[i];
			asteroids[i] = nullptr;
		}
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
			player->Shoot(window);
		}
		// If esc is released
		if (event.key.code == sf::Keyboard::Escape)
		{
			// Quit game
			window->close();
			delete player;
			player = nullptr;
			for (int i = 0; i < enemies.size(); i++)
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
			for (int i = 0; i < asteroids.size(); i++)
			{
				delete asteroids[i];
				asteroids[i] = nullptr;
			}
			for (int i = 0; i < stars.size(); i++)
			{
				delete stars[i];
				stars[i] = nullptr;
			}

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
			player->Shoot(window);
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
