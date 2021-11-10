#include <iostream>
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <fstream>
#include <vector>
#include "EventController.h"
#include "Player.h"
#include "EnemyBoss.h"
#include "Asteroid.h"
#include "DatabaseManager.h"

void Reload(int &_score, int &_highScore, int _maxLife, int &_playerLife, Player* _player, sf::RenderWindow* window, std::vector<Enemy*> &_enemies, std::vector<Asteroid*> &_asteroids, std::vector<EnemyBoss*> &_enemyBoss, DatabaseManager* _databaseManager, int& _playerDeathCount)
{
	if (_player->GetHealth() <= 0)
	{
		_playerDeathCount++;
		// Update the highscore
		if (_highScore < _score)
		{
			_highScore = _score;
		}

		// Reset the score and playerLife
		_score = 0;
		_playerLife = _maxLife;
		_player->SetHealth(_maxLife);

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
		_databaseManager->UpdatePlayerDeath(_playerDeathCount);
		// Reload the game
		window->clear();
	}
}

// This is basically my game manager. Should have made a new class for it
int main()
{
	DatabaseManager* databaseManager = new DatabaseManager();
	std::ifstream inputStream("./JSON/Main.json");
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);

	sf::View view;
	float width = document["width"].ToFloat(), height = document["height"].ToFloat();
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), document["name"].ToString());
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

	int score = 0;
	int highScore = 0;
	int playerMaxLife = player->GetHealth();
	int playerLife = player->GetHealth();
	
	// Database stuff
	int playerDeath = 0;
	int enemyKilled = 0;
	int asteroidKilled = 0;
	int collisionDeath = 0;
	int bossKilled = 0;
	databaseManager->UpdatePlayerDeath(playerDeath);
	databaseManager->UpdateSpaceShipDead(enemyKilled);
	databaseManager->UpdateAsteroidDead(asteroidKilled);
	databaseManager->UpdatePlayerDeathByCollision(collisionDeath);
	databaseManager->UpdateBossKilled(bossKilled);

	// Loading image texture
	sf::Texture backgroundTexture;
	// If this failed
	if (backgroundTexture.loadFromFile(document["background"].ToString()) == false)
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
	if (font.loadFromFile(document["font"].ToString()) == false)
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
			eventController.HandleEvents(event, window, player, enemies, asteroids, stars, databaseManager);
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
					Reload(score, highScore, playerMaxLife, playerLife, player, window, enemies, asteroids, enemybosses, databaseManager, playerDeath);
					scoreText.setString("Score: " + std::to_string(score));
					lifeText.setString("Life: " + std::to_string(playerLife));
					highScoreText.setString("Highscore: " + std::to_string(highScore));
					collisionDeath++;
					databaseManager->UpdatePlayerDeathByCollision(collisionDeath);
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
								asteroids[i]->SetHealth(asteroids[i]->GetHealth() - player->GetProjectileList()[j]->GetDamage());

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
			asteroidKilled++;
			delete(asteroids[toBeDeleted[k]]);
			asteroids[toBeDeleted[k]] = nullptr;
			asteroids.erase(asteroids.begin() + toBeDeleted[k]);
			databaseManager->UpdateAsteroidDead(asteroidKilled);
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
					player->SetHealth(player->GetHealth() - enemies[i]->GetProjectileList()[j]->GetDamage());
					playerLife = player->GetHealth();
					lifeText.setString("Life: " + std::to_string(playerLife));
					
					// Detroy the enemy projectile that hits the player
					delete(enemies[i]->GetProjectileList()[j]);
					enemies[i]->GetProjectileList()[j] = nullptr;
					enemies[i]->GetProjectileList().erase(enemies[i]->GetProjectileList().begin() + j);

					// Reload the game if the player dies
					if (player->GetHealth() <= 0)
					{
						Reload(score, highScore, playerMaxLife, playerLife, player, window, enemies, asteroids, enemybosses, databaseManager, playerDeath);
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
					Reload(score, highScore, playerMaxLife, playerLife, player, window, enemies, asteroids, enemybosses, databaseManager, playerDeath);
					scoreText.setString("Score: " + std::to_string(score));
					lifeText.setString("Life: " + std::to_string(playerLife));
					highScoreText.setString("Highscore: " + std::to_string(highScore));
					collisionDeath++;
					databaseManager->UpdatePlayerDeathByCollision(collisionDeath);
					break;
				}

				// Check if the enemy collides with the player projectiles
				for (int k = 0; k < player->GetProjectileList().size(); k++)
				{
					if (enemies[i]->GetSprite()->getGlobalBounds().intersects(player->GetProjectileList()[k]->GetSprite()->getGlobalBounds()))
					{
						// Just to be safe
						if (enemies[i]->GetHealth() > 0)
						{
							// Calculate the health remaining
							enemies[i]->SetHealth(enemies[i]->GetHealth() - player->GetProjectileList()[k]->GetDamage());

							// Add it to toBeDeleted it if its health is below 0
							if (enemies[i]->GetHealth() <= 0)
							{
								toBeDeleted.push_back(i);
								score += enemies[i]->GetScore();
							}
						}
						// Delete the player projectile that hits the enemy
						delete(player->GetProjectileList()[k]);
						player->GetProjectileList()[k] = nullptr;
						player->GetProjectileList().erase(player->GetProjectileList().begin() + k);
					}
				}
			}
		}

		// Clear the enemybosses list
		for (int k = 0; k < toBeDeleted.size(); k++)
		{
			enemyKilled++;
			delete(enemies[toBeDeleted[k]]);
			enemies[toBeDeleted[k]] = nullptr;
			enemies.erase(enemies.begin() + toBeDeleted[k]);
			databaseManager->UpdateSpaceShipDead(enemyKilled);
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
					Reload(score, highScore, playerMaxLife, playerLife, player, window, enemies, asteroids, enemybosses, databaseManager, playerDeath);
					scoreText.setString("Score: " + std::to_string(score));
					lifeText.setString("Life: " + std::to_string(playerLife));
					highScoreText.setString("Highscore: " + std::to_string(highScore));
					collisionDeath++;
					databaseManager->UpdatePlayerDeathByCollision(collisionDeath);
					break;
				}

				// Check if the enemybosses collides with the player projectiles
				for (int k = 0; k < player->GetProjectileList().size(); k++)
				{
					if (enemybosses[i]->GetSprite()->getGlobalBounds().intersects(player->GetProjectileList()[k]->GetSprite()->getGlobalBounds()))
					{

						// Just to be safe
						if (enemybosses[i]->GetHealth() > 0)
						{
							// Calculate the health remaining
							enemybosses[i]->SetHealth(enemybosses[i]->GetHealth() - player->GetProjectileList()[k]->GetDamage());

							// Add it to toBeDeleted it if its health is below 0
							if (enemybosses[i]->GetHealth() <= 0)
							{
								toBeDeleted.push_back(i);
								score += enemybosses[i]->GetScore();
							}
						}
						// Delete the player projectile that hits the enemy
						delete(player->GetProjectileList()[k]);
						player->GetProjectileList()[k] = nullptr;
						player->GetProjectileList().erase(player->GetProjectileList().begin() + k);
					}
				}

			}
		}

		// Clear the enemybosses list
		for (int k = 0; k < toBeDeleted.size(); k++)
		{
			bossKilled++;
			delete(enemybosses[toBeDeleted[k]]);
			enemybosses[toBeDeleted[k]] = nullptr;
			enemybosses.erase(enemybosses.begin() + toBeDeleted[k]);
			databaseManager->UpdateBossKilled(bossKilled);
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
					player->SetHealth(player->GetHealth() - enemybosses[i]->GetProjectileList()[j]->GetDamage());
					playerLife = player->GetHealth();
					lifeText.setString("Life: " + std::to_string(playerLife));

					// Detroy the enemy projectile that hits the player
					delete(enemybosses[i]->GetProjectileList()[j]);
					enemybosses[i]->GetProjectileList()[j] = nullptr;
					enemybosses[i]->GetProjectileList().erase(enemybosses[i]->GetProjectileList().begin() + j);

					// Reload the game if the player dies
					if (player->GetHealth() <= 0)
					{
						Reload(score, highScore, playerMaxLife, playerLife, player, window, enemies, asteroids, enemybosses, databaseManager, playerDeath);
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
	delete databaseManager;
	delete window;
}