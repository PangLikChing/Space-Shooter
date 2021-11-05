#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "EventController.h"
#include "Player.h"
#include "EnemyBoss.h"
#include "Asteroid.h"

void Reload(int &_score, int &_highScore, int &_playerLife, Player* _player, sf::RenderWindow* window, std::vector<Enemy*> &_enemies, std::vector<Asteroid*> &_asteroids, std::vector<EnemyBoss*> &_enemyBoss)
{
	if (_player->GetHealth() <= 0)
	{
		// Update the highscore
		if (_highScore < _score)
		{
			_highScore = _score;
		}

		// Reset the score and playerLife
		_score = 0;
		_playerLife = 3;
		_player->SetHealth(3);

		// Delete everything except the player
		for (int i = 0; i < _enemies.size(); i++)
		{
			delete _enemies[i];
			_enemies[i] = nullptr;
		}

		for (int i = 0; i < _enemyBoss.size(); i++)
		{
			delete _enemyBoss[i];
			_enemyBoss[i] = nullptr;
		}

		for (int i = 0; i < _asteroids.size(); i++)
		{
			delete _asteroids[i];
			_asteroids[i] = nullptr;
		}

		_enemyBoss.clear();
		_enemies.clear();
		_asteroids.clear();
		// Reset Player position
		_player->GetSprite()->setPosition(0, 0);
		// Reload the game
		window->clear();
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

	// Initializing player, enemies and stars timer
	Player* player = new Player();
	std::vector<Enemy*> enemies = {};
	std::vector<Asteroid*> asteroids = {};
	std::vector<Star*> stars = {};
	std::vector<EnemyBoss*> enemybosses = {};
	int enemySpawnTimer = 0;
	int asteroidSpawnTimer = 0;
	int starSpawnTimer = 0;
	int enemyBossSpawnTimer = 0;
	

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
			eventController.HandleEvents(event, window, player, enemies, asteroids, stars);
		}

		// Spawn stars every 4 second
		if (starSpawnTimer < 240)
		{
			starSpawnTimer++;
		}
		else
		{
			Star* star = new Star(window);
			stars.push_back(star);
			starSpawnTimer = 0;
		}

		// Draw Stars
		for (int i = 0; i < stars.size(); i++)
		{
			if (stars[i] != nullptr)
			{
				// Draw
				stars[i]->DrawObject(window);
			}
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
					std::cout << "RELOADDDDDDDDDDDDDDDDDDDDDDDDDDD" << std::endl;
					player->SetHealth(0);
					Reload(score, highScore, playerLife, player, window, enemies, asteroids, enemybosses);
					scoreText.setString("Score: " + std::to_string(score));
					lifeText.setString("Life: " + std::to_string(playerLife));
					highScoreText.setString("Highscore: " + std::to_string(highScore));
					break;
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

		// See if the enemy projectile hits the player
		for (int i = 0; i < enemies.size(); i++)
		{
			for (int j = 0; j < enemies[i]->GetProjectileList().size(); j++)
			{
				if (enemies[i]->GetProjectileList()[j]->GetSprite()->getGlobalBounds().intersects(player->GetSprite()->getGlobalBounds()))
				{
					// Calculate the player life remaining
					player->SetHealth(player->GetHealth() - 1);
					playerLife -= 1;
					lifeText.setString("Life: " + std::to_string(playerLife));
					
					// Detroy the enemy projectile that hits the player
					delete(enemies[i]->GetProjectileList()[j]);
					enemies[i]->GetProjectileList()[j] = nullptr;
					enemies[i]->GetProjectileList().erase(enemies[i]->GetProjectileList().begin() + j);

					// Reload the game if the player dies
					if (player->GetHealth() <= 0)
					{
						Reload(score, highScore, playerLife, player, window, enemies, asteroids, enemybosses);
						scoreText.setString("Score: " + std::to_string(score));
						lifeText.setString("Life: " + std::to_string(playerLife));
						highScoreText.setString("Highscore: " + std::to_string(highScore));
						break;
					}
				}
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
					player->SetHealth(0);
					Reload(score, highScore, playerLife, player, window, enemies, asteroids, enemybosses);
					scoreText.setString("Score: " + std::to_string(score));
					lifeText.setString("Life: " + std::to_string(playerLife));
					highScoreText.setString("Highscore: " + std::to_string(highScore));
					break;
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
							}
						}
					}
				}
			}
		}

		// Clear the enemybosses list
		for (int k = 0; k < toBeDeleted.size(); k++)
		{
			delete(enemies[toBeDeleted[k]]);
			enemies[toBeDeleted[k]] = nullptr;
			enemies.erase(enemies.begin() + toBeDeleted[k]);
		}
		toBeDeleted.clear();

		// Spawn enemies every 15 second
		if (enemyBossSpawnTimer < 900)
		{
			enemyBossSpawnTimer++;
		}
		else
		{
			EnemyBoss* enemyboss = new EnemyBoss(window);
			enemybosses.push_back(enemyboss);
			enemyBossSpawnTimer = 0;
		}

		// Move enemyboss
		for (int i = 0; i < enemybosses.size(); i++)
		{
			if (enemybosses[i] != nullptr)
			{
				enemybosses[i]->DrawObject(window);

				// EnemyBosses shoot twice every 1 seconds
				if (enemybosses[i]->GetShootTimer() < 60)
				{
					enemybosses[i]->SetShootTimer(enemybosses[i]->GetShootTimer() + 1);
				}
				else if (enemybosses[i]->GetShootTimer() == 60 || enemybosses[i]->GetShootTimer() == 80)
				{
					// Enemy Shoot
					enemybosses[i]->Shoot(window);
					enemybosses[i]->SetShootTimer(enemybosses[i]->GetShootTimer() + 1);
				}
				else if (enemybosses[i]->GetShootTimer() > 60 && enemybosses[i]->GetShootTimer() <= 79)
				{
					enemybosses[i]->SetShootTimer(enemybosses[i]->GetShootTimer() + 1);
				}
				else if (enemybosses[i]->GetShootTimer() >= 80)
				{
					// Enemybosses Shoot
					enemybosses[i]->SetShootTimer(0);
				}

				// Draw enemybosses projectile
				for (int j = 0; j < enemybosses[i]->GetProjectileList().size(); j++)
				{
					enemybosses[i]->GetProjectileList()[j]->DrawObject(window);
				}

				// Check if the enemybosses collides with the player
				if (enemybosses[i]->GetSprite()->getGlobalBounds().intersects(player->GetSprite()->getGlobalBounds()))
				{
					// Reload Game
					std::cout << "RELOADDDDDDDDDDDDDDDDDDDDDDDDDDD" << std::endl;
					player->SetHealth(0);
					Reload(score, highScore, playerLife, player, window, enemies, asteroids, enemybosses);
					scoreText.setString("Score: " + std::to_string(score));
					lifeText.setString("Life: " + std::to_string(playerLife));
					highScoreText.setString("Highscore: " + std::to_string(highScore));
					break;
				}

				// Check if the enemybosses collides with the player projectiles
				for (int k = 0; k < player->GetProjectileList().size(); k++)
				{
					if (enemybosses[i]->GetSprite()->getGlobalBounds().intersects(player->GetProjectileList()[k]->GetSprite()->getGlobalBounds()))
					{
						// Delete the player projectile that hits the enemy
						delete(player->GetProjectileList()[k]);
						player->GetProjectileList()[k] = nullptr;
						player->GetProjectileList().erase(player->GetProjectileList().begin() + k);

						// Just to be safe
						if (enemybosses[i]->GetHealth() > 0)
						{
							// Calculate the health remaining
							enemybosses[i]->SetHealth(enemybosses[i]->GetHealth() - 1);

							// Add it to toBeDeleted it if its health is below 0
							if (enemybosses[i]->GetHealth() <= 0)
							{
								toBeDeleted.push_back(i);
								score += enemybosses[i]->GetScore();
							}
						}
					}
				}

			}
		}

		// Clear the enemybosses list
		for (int k = 0; k < toBeDeleted.size(); k++)
		{
			delete(enemybosses[toBeDeleted[k]]);
			enemybosses[toBeDeleted[k]] = nullptr;
			enemybosses.erase(enemybosses.begin() + toBeDeleted[k]);
		}
		toBeDeleted.clear();

		// See if the enemyboss projectile hits the player
		for (int i = 0; i < enemybosses.size(); i++)
		{
			for (int j = 0; j < enemybosses[i]->GetProjectileList().size(); j++)
			{
				if (enemybosses[i]->GetProjectileList()[j]->GetSprite()->getGlobalBounds().intersects(player->GetSprite()->getGlobalBounds()))
				{
					// Calculate the player life remaining
					player->SetHealth(player->GetHealth() - 1);
					playerLife -= 1;
					lifeText.setString("Life: " + std::to_string(playerLife));

					// Detroy the enemy projectile that hits the player
					delete(enemybosses[i]->GetProjectileList()[j]);
					enemybosses[i]->GetProjectileList()[j] = nullptr;
					enemybosses[i]->GetProjectileList().erase(enemybosses[i]->GetProjectileList().begin() + j);

					// Reload the game if the player dies
					if (player->GetHealth() <= 0)
					{
						Reload(score, highScore, playerLife, player, window, enemies, asteroids, enemybosses);
						scoreText.setString("Score: " + std::to_string(score));
						lifeText.setString("Life: " + std::to_string(playerLife));
						highScoreText.setString("Highscore: " + std::to_string(highScore));
						break;
					}
				}
			}
		}

		// Delete stars out of bounds
		for (int i = 0; i < stars.size(); i++)
		{
			if (stars[i]->GetSprite()->getPosition().y >= window->getSize().y * 0.5f)
			{
				delete(stars[i]);
				stars[i] = nullptr;
				stars.erase(stars.begin() + i);
			}
		}

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

		// Delete enemies out of bounds
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->GetSprite()->getPosition().y >= window->getSize().y * 0.5f)
			{
				delete(enemies[i]);
				enemies[i] = nullptr;
				enemies.erase(enemies.begin() + i);
			}
		}

		// Delete enemybosses out of bounds
		for (int i = 0; i < enemybosses.size(); i++)
		{
			if (enemybosses[i]->GetSprite()->getPosition().y >= window->getSize().y * 0.5f)
			{
				delete(enemybosses[i]);
				enemybosses[i] = nullptr;
				enemybosses.erase(enemybosses.begin() + i);
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

	for (int i = 0; i < enemybosses.size(); i++)
	{
		delete enemybosses[i];
		enemybosses[i] = nullptr;
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

	delete player;
	delete window;
}