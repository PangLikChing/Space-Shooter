#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "EventController.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
	sf::View view;
	float width = 600.0f, height = 768.0f;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "SPACE SHOOTER!");
	float halfWidth = window->getSize().x * 0.5f;
	float halfHeight = window->getSize().y * 0.5f;
	view.reset(sf::FloatRect(-halfWidth, -halfHeight, halfWidth * 2.0f, halfHeight * 2.0f));
	window->setView(view);
	window->setFramerateLimit(60);

	// Initializing players and enemies
	Player* player = new Player();
	std::vector<Enemy*> enemies = {};
	float enemySpawnTimer = 0;

	// Loading image texture
	sf::Texture backgroundTexture;
	// If this failed
	if (backgroundTexture.loadFromFile("starBackground.png") == false)
	{
		return 0;
	}

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setOrigin(sf::Vector2f(backgroundTexture.getSize().x * 0.5f, backgroundTexture.getSize().y * 0.5f));
	backgroundSprite.setScale(width / backgroundSprite.getLocalBounds().width, height / backgroundSprite.getLocalBounds().height);

	// Loading text font
	sf::Font font;
	// If this failed
	if (font.loadFromFile("courbd.ttf") == false)
	{
		return 0;
	}

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setString("SPACE SHOOTER!");
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width * 0.5f, text.getLocalBounds().height * 7.5f));

	EventController* eventController = new EventController();
	// Game Loop
	while (window != nullptr)
	{
		window->clear();

		// Draw Background
		window->draw(backgroundSprite);

		sf::Event event;
		while (window->isOpen() == true && window->pollEvent(event))
		{
			eventController->HandleEvents(event, window, player);

		}

		player->DrawObject(window);

		// Spawn enemies every 1 second
		if (enemySpawnTimer < 60)
		{
			enemySpawnTimer++;
		}
		else
		{
			Enemy* enemy = new Enemy(window);
			enemies.push_back(enemy);
			enemySpawnTimer = 0;
		}
		// Move enemies
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->DrawObject(window);
		}
		//test

		window->draw(text);

		window->display();
	}

	delete player;
	delete eventController;
	delete window;
}
