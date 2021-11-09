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

	void Update();
};

#endif // !DATABASEMANAGER_H