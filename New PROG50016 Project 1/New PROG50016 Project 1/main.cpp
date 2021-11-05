#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "EventController.h"
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"

void Reload(int _playerLife, sf::RenderWindow* window)
{
	if (_playerLife <= 0)
	{
		// Reload the game
		window->clear();

		// Reset the score


		// Update the highscore
		// Delete everything except the player
	}
}

// This is basically my game manager. Should have made a new class for it
int main()
{
	int score = 0;
	int highScore = 0;
	int playerLife = 3;

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
	lifeText.setString("Life: " + std::to_string(playerLife));
	lifeText.setPosition(window->getSize().x * -0.45f, window->getSize().y * 0.4f);

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setPosition(window->getSize().x * -0.45f, window->getSize().y * -0.45f);

	sf::Text highScoreText;
	highScoreText.setFont(font);
	highScoreText.setCharacterSize(30);
	highScoreText.setFillColor(sf::Color::Red);
	highScoreText.setOutlineColor(sf::Color::Black);
	highScoreText.setString("Highscore: " + std::to_string(highScore));
	highScoreText.setPosition(window->getSize().x * -0.45f, window->getSize().y * -0.5f);

	EventController eventController;
	std::vector<int> toBeDeleted = {};

	// Game Loop
	while (window != nullptr)
	{
		window->clear();

		// Draw Background
		window->draw(backgroundSprite);

		sf::Event event;
		while (window->isOpen() == true && window->pollEvent(event) && window != nullptr)
		{
			eventController.HandleEvents(event, window, player, enemies, asteroids);
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

		// Draw Projectiles
		for (int i = 0; i < player->GetProjectileList().size(); i++)
		{
			if (player->GetProjectileList()[i] != nullptr)
			{
				// Draw
				player->GetProjectileList()[i]->DrawObject(window);
			}
		}

		// Move asteroids
		for (int i = 0; i < asteroids.size(); i++)
		{
			if (asteroids[i] != nullptr)
			{
				asteroids[i]->DrawObject(window);
				// See if the asteroids collides with the player
				if (asteroids[i]->GetSprite()->getGlobalBounds().intersects(player->GetSprite()->getGlobalBounds()))
				{
					//std::cout << "RELOADDDDDDDDDDDDDDDDDDDDDDDDDDD" << std::endl;
					toBeDeleted.push_back(i);
				}
				// See if the asteroids collides with the player projectile
				for (int j = 0; j < player->GetProjectileList().size(); j++)
				{
					if (player->GetProjectileList()[j] != nullptr && asteroids[i] != nullptr)
					{
						if (asteroids[i]->GetSprite()->getGlobalBounds().intersects(player->GetProjectileList()[j]->GetSprite()->getGlobalBounds()))
						{
							// Delete player projectile that shoot the asteroids
							delete(player->GetProjectileList()[j]);
							player->GetProjectileList()[j] = nullptr;
							player->GetProjectileList().erase(player->GetProjectileList().begin() + j);
							// Just to be safe
							if (asteroids[i]->GetHealth() > 0)
							{
								// Calculate the health remaining
								asteroids[i]->SetHealth(asteroids[i]->GetHealth() - 1);

								// Add it to toBeDeleted it if its health is below 0
								if (asteroids[i]->GetHealth() <= 0)
								{
									toBeDeleted.push_back(i);
								}
							}
						}
					}
				}
			}
		}
		// Clear the asteroids list
		for (int k = 0; k < toBeDeleted.size(); k++)
		{
			delete(asteroids[toBeDeleted[k]]);
			asteroids[toBeDeleted[k]] = nullptr;
			asteroids.erase(asteroids.begin() + toBeDeleted[k]);
		}
		// Clear the toBeDeleted list
		toBeDeleted.clear();

		// Delete asteroids out of bounds
		for (int i = 0; i < asteroids.size(); i++)
		{
			if (asteroids[i]->GetSprite()->getPosition().y >= window->getSize().y * 0.5f)
			{
				delete(asteroids[i]);
				asteroids[i] = nullptr;
				asteroids.erase(asteroids.begin() + i);
			}
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
			if (enemies[i] != nullptr) 
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
				// Check if the enemy collides with the player
				if (enemies[i]->GetSprite()->getGlobalBounds().intersects(player->GetSprite()->getGlobalBounds()))
				{
					// Reload Game
					std::cout << "RELOADDDDDDDDDDDDDDDDDDDDDDDDDDD" << std::endl;
					toBeDeleted.push_back(i);
				}
				// Check if the enemy collides with the player projectiles
				for (int k = 0; k < player->GetProjectileList().size(); k++)
				{
					if (enemies[i]->GetSprite()->getGlobalBounds().intersects(player->GetProjectileList()[k]->GetSprite()->getGlobalBounds()))
					{
						// Delete the player projectile that hits the enemy
						delete(player->GetProjectileList()[k]);
						player->GetProjectileList()[k] = nullptr;
						player->GetProjectileList().erase(player->GetProjectileList().begin() + k);
						// Just to be safe
						if (enemies[i]->GetHealth() > 0)
						{
							// Calculate the health remaining
							enemies[i]->SetHealth(enemies[i]->GetHealth() - 1);

							// Add it to toBeDeleted it if its health is below 0
							if (enemies[i]->GetHealth() <= 0)
							{
								toBeDeleted.push_back(i);
								score += enemies[i]->GetScore();
								std::cout << "Score is " << score << std::endl;
							}
						}
					}
				}
			}
		}
		// Clear the enemies list
		for (int k = 0; k < toBeDeleted.size(); k++)
		{
			delete(enemies[toBeDeleted[k]]);
			enemies[toBeDeleted[k]] = nullptr;
			enemies.erase(enemies.begin() + toBeDeleted[k]);
		}
		toBeDeleted.clear();

		// Delete useless enemies
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->GetSprite()->getPosition().y >= window->getSize().y * 0.5f)
			{
				delete(enemies[i]);
				enemies[i] = nullptr;
				enemies.erase(enemies.begin() + i);
			}
		}

		//Update the scoreText
		scoreText.setString("Score: " + std::to_string(score));

		// Draw Player
		player->DrawObject(window);

		// Draw the UI
		window->draw(lifeText);
		window->draw(scoreText);
		window->draw(highScoreText);

		// Display the window
		window->display();
	}
	// Delete objects
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
	delete window;
}