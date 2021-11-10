#include "DatabaseManager.h"
#include <cassert>

DatabaseManager::DatabaseManager()
{
	std::cout << "DatabaseManager Created" << std::endl;
}

DatabaseManager::~DatabaseManager()
{
	std::cout << "DatabaseManager Destroyed" << std::endl;
}

void DatabaseManager::Create()
{
	int id = 1;
	// Open database
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	// Make statement
	std::string statement = "INSERT INTO Data (id) VALUES (@id);";

	sqlite3_stmt* stm;
	int result = sqlite3_prepare_v2(db, statement.c_str(), -1, &stm, 0);

	if (result == SQLITE_OK)
	{
		// Excute statement
		int index = sqlite3_bind_parameter_index(stm, "@id");
		sqlite3_bind_int(stm, index, id);

		result = sqlite3_step(stm);
		sqlite3_finalize(stm);
		if (result != SQLITE_DONE)
		{
			std::cout << "Error" << std::endl;
		}
	}
	else
	{
		std::cout << "Failed to prepare statement" << sqlite3_errmsg(db) << std::endl;
	}

	// Close database
	sqlite3_close(db);
}

sqlite3* DatabaseManager::Open()
{
	sqlite3* db = nullptr;

	int result = sqlite3_open("Data.db", &db);
	if (result)
	{
		std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return nullptr;
	}

	std::cout << "Opened database successfully" << std::endl;
	return db;
}

int ReadCallback(void* data, int argc, char** argv, char** azColName)
{
	// Data is what we pass in, could be string / object / etc
	std::cout << (const char*)data << std::endl;
	for (int i = 0; i < argc; i++)
	{
		std::cout << azColName[i] << " " << argv[i] << std::endl;
	}
	std::cout << std::endl;
	return 0;
}

void DatabaseManager::Read()
{
	char* errMessage = nullptr;
	// Open DB
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	std::string statement = "SELECT * FROM Data";
	int result = sqlite3_exec(db, statement.c_str(), ReadCallback, (void*)"Custom Message", &errMessage);
	if (result != SQLITE_OK)
	{
		std::cout << "Error executing read: " << errMessage << std::endl;
		sqlite3_free(errMessage);
	}

	sqlite3_close(db);
}

void DatabaseManager::UpdatePlayerDeath(int _playerDeath)
{
	// Open DB
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	int playerDeath = _playerDeath;
	// id can be changed later if neccessary. id is only useful if the data has multiple enterence
	//int id = 1;

	//std::string sql_statement = "UPDATE Data SET playerDeath = @playerDeath WHERE id = @id;";
	std::string sql_statement = "UPDATE Data SET playerDeath = @playerDeath";
	sqlite3_stmt* statement = nullptr;
	int result = sqlite3_prepare_v2(db, sql_statement.c_str(), -1, &statement, nullptr);
	if (result == SQLITE_OK)
	{
		//int index = sqlite3_bind_parameter_index(statement, "@id");
		//sqlite3_bind_int(statement, index, id);

		int index2 = sqlite3_bind_parameter_index(statement, "@playerDeath");
		sqlite3_bind_int(statement, index2, playerDeath);

		result = sqlite3_step(statement);
		sqlite3_finalize(statement);
	}
	else
	{
		std::cout << "Error" << std::endl;
	}

	sqlite3_close(db);
}

// Not Updated
void DatabaseManager::UpdateSpaceShipDead(int _spaceShipDead)
{
	// Open DB
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	int spaceShipDead = _spaceShipDead;

	std::string sql_statement = "UPDATE Data SET spaceShipDead = @spaceShipDead;";
	sqlite3_stmt* statement = nullptr;
	int result = sqlite3_prepare_v2(db, sql_statement.c_str(), -1, &statement, nullptr);
	if (result == SQLITE_OK)
	{
		int index = sqlite3_bind_parameter_index(statement, "@spaceShipDead");
		sqlite3_bind_int(statement, index, spaceShipDead);

		result = sqlite3_step(statement);
		sqlite3_finalize(statement);
	}
	else
	{
		std::cout << "Error" << std::endl;
	}

	sqlite3_close(db);
}

// Not Updated
void DatabaseManager::UpdateAsteroidDead(int _asteroidDead)
{
	// Open DB
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	int asteroidDead = _asteroidDead;

	std::string sql_statement = "UPDATE Data SET asteroidDead = @asteroidDead;";
	sqlite3_stmt* statement = nullptr;
	int result = sqlite3_prepare_v2(db, sql_statement.c_str(), -1, &statement, nullptr);
	if (result == SQLITE_OK)
	{
		int index = sqlite3_bind_parameter_index(statement, "@asteroidDead");
		sqlite3_bind_int(statement, index, asteroidDead);

		result = sqlite3_step(statement);
		sqlite3_finalize(statement);
	}
	else
	{
		std::cout << "Error" << std::endl;
	}

	sqlite3_close(db);
}

// Not Updated
void DatabaseManager::UpdatePlayerDeathByCollision(int _collisionDeath)
{
	// Open DB
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	int collisionDeath = _collisionDeath;

	std::string sql_statement = "UPDATE Data SET playerDeathByCollision = @collisionDeath;";
	sqlite3_stmt* statement = nullptr;
	int result = sqlite3_prepare_v2(db, sql_statement.c_str(), -1, &statement, nullptr);
	if (result == SQLITE_OK)
	{
		int index = sqlite3_bind_parameter_index(statement, "@collisionDeath");
		sqlite3_bind_int(statement, index, collisionDeath);

		result = sqlite3_step(statement);
		sqlite3_finalize(statement);
	}
	else
	{
		std::cout << "Error" << std::endl;
	}

	sqlite3_close(db);
}

// Not Updated
void DatabaseManager::UpdateBossKilled(int _bosskilled)
{
	// Open DB
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	int bossKilled = _bosskilled;

	std::string sql_statement = "UPDATE Data SET numberOfBossKilled = @bossKilled;";
	sqlite3_stmt* statement = nullptr;
	int result = sqlite3_prepare_v2(db, sql_statement.c_str(), -1, &statement, nullptr);
	if (result == SQLITE_OK)
	{
		int index = sqlite3_bind_parameter_index(statement, "@bossKilled");
		sqlite3_bind_int(statement, index, bossKilled);

		result = sqlite3_step(statement);
		sqlite3_finalize(statement);
	}
	else
	{
		std::cout << "Error" << std::endl;
	}

	sqlite3_close(db);
}
