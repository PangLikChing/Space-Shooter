#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <iostream>
#include "sqlite3.h"

class DatabaseManager
{
public:
	DatabaseManager();

	~DatabaseManager();

	void Create();

	sqlite3* Open();

	void Read();

	void UpdatePlayerDeath(int _playerDeath);

	void UpdateSpaceShipDead(int _spaceShipDead);

	void UpdateAsteroidDead(int _asteroidDead);

	void UpdatePlayerDeathByCollision(int _collisionDeath);

	void UpdateBossKilled(int _bosskilled);
};

#endif // !DATABASEMANAGER_H