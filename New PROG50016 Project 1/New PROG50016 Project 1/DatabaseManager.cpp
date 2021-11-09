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
	std::string name = "";
	// Open database
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	// Make statement
	std::string statement = "INSERT INTO Example_Table (name) VALUES (@name);";

	sqlite3_stmt* stm;
	int result = sqlite3_prepare_v2(db, statement.c_str(), -1, &stm, 0);

	if (result == SQLITE_OK)
	{
		// Excute statement
		int index = sqlite3_bind_parameter_index(stm, "@name");
		sqlite3_bind_text(stm, index, name.c_str(), name.length(), nullptr);

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

	int result = sqlite3_open("Example.db", &db);
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

	std::string statement = "SELECT * FROM Example_Table";
	int result = sqlite3_exec(db, statement.c_str(), ReadCallback, (void*)"Custom Message", &errMessage);
	if (result != SQLITE_OK)
	{
		std::cout << "Error executing read: " << errMessage << std::endl;
		sqlite3_free(errMessage);
	}

	sqlite3_close(db);
}

void DatabaseManager::Update()
{
	// Open DB
	sqlite3* db = Open();
	assert(db != nullptr, "Unable to open database");

	int id = -1;
	//std::cout << "Enter id to update: ";
	//std::cin >> id;

	std::string sql_statement = "UPDATE Example_Table SET name = @name WHERE id = @id";
	sqlite3_stmt* statement = nullptr;
	int result = sqlite3_prepare_v2(db, sql_statement.c_str(), -1, &statement, nullptr);
	if (result == SQLITE_OK)
	{
		int index = sqlite3_bind_parameter_index(statement, "@id");
		sqlite3_bind_int(statement, index, id);

		result = sqlite3_step(statement);
		sqlite3_finalize(statement);
	}
	else
	{
		std::cout << "Error" << std::endl;
	}

	sqlite3_close(db);
}
