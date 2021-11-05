#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "EventController.h"
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"

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

	// Initializing players and enemies timer
	Player* player = new Player();
	std::vector<Enemy*> enemies = {};
	std::vector<Asteroid*> asteroids = {};
	float enemySpawnTimer = 0;
	float asteroidSpawnTimer = 0;

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

	sf::Text lifeText;
	lifeText.setFont(font);
	lifeText.setCharacterSize(30);
	lifeText.setFillColor(sf::Color::Green);
	lifeText.setOutlineColor(sf::Color::Black);
	lifeText.setString("Life: 3");
	lifeText.setPosition(window->getSize().x * -0.45f, window->getSize().y * 0.4f);

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setString("Score: 0");
	scoreText.setPosition(window->getSize().x * -0.45f, window->getSize().y * -0.45f);

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
			eventController->HandleEvents(event, window, player, enemies, asteroids);
		}

		// Spawn asteroids every 8 second
		if (asteroidSpawnTimer < 480)
		{
			asteroidSpawnTimer++;
		}
		else
		{
			Asteroid* asteroid = new Asteroid(window);
			asteroids.push_back(asteroid);
			asteroidSpawnTimer = 0;
		}
		// Move enemies
		for (int i = 0; i < asteroids.size(); i++)
		{
			asteroids[i]->DrawObject(window);
		}

		// Spawn enemies every 2 second
		if (enemySpawnTimer < 120)
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

			// Enemies shoot every 1 seconds
			if (enemies[i]->GetShootTimer() < 60)
			{
				enemies[i]->SetShootTimer(enemies[i]->GetShootTimer() + 1);
			}
			else
			{
				// Enemy Shoot
				enemies[i]->Shoot(window);
				enemies[i]->SetShootTimer(0);
			}

			// Draw enemy projectile
			for (int j = 0; j < enemies[i]->GetProjectileList().size(); j++)
			{
				enemies[i]->GetProjectileList()[j]->DrawObject(window);
			}

			// Delete useless enemies
			if (enemies[i]->GetSprite()->getPosition().y >= window->getSize().y * 0.5f)
			{
				delete(enemies[i]);
				enemies[i] = nullptr;
				enemies.erase(enemies.begin() + i);
			}
		}

		std::vector<Projectile*> tmp = player->GetProjectileList();

		for (int i = 0; i < player->GetProjectileList().size(); i++)
		{
			if (player->GetProjectileList()[i] != nullptr)
			{
				// Draw
				player->GetProjectileList()[i]->DrawObject(window);
			}
		}

		// Draw Player
		player->DrawObject(window);

		window->draw(lifeText);
		window->draw(scoreText);

		window->display();
	}
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
	delete player;
	delete eventController;
	delete window;
}
