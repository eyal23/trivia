#include <io.h>
#include <exception>
#include <vector>
#include <map>

#include "sqliteDataBase.h"
#include "sqlite3.h"

#define DATABASE_NAME "triviaDB.sqlite"

using std::exception;
using std::vector;
using std::map;


SqliteDatabase::SqliteDatabase()
{
	int isExisting = _access(DATABASE_NAME, 0);

	if (sqlite3_open(DATABASE_NAME, &this->m_db) == SQLITE_OK)
	{
		if (isExisting == -1)
		{
			if (initDatabase())
			{
				throw exception("Could'nt initialize database");
			}
		}
	}
	else
	{
		throw exception("Could'nt open database");
	}
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(this->m_db);
}

bool SqliteDatabase::doesUserExist(string username)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "USERS" },
		{},
		{ "USERNAME" },
		{
			{ "USERNAME", username },
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	return result.size() != 0;
}

bool SqliteDatabase::doesPasswordMatch(string username, string password)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "USERS" },
		{},
		{ "USERNAME" },
		{
			{ "USERNAME", username },
			{ "PASSWORD", password }
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	return result.size() != 0;
}

void SqliteDatabase::addNewUser(string username, string password, string email)
{
	InsertQuery query = {
		"USERS",
		{
			username,
			password,
			email
		},
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query), nullptr, nullptr, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}
}

bool SqliteDatabase::initDatabase()
{
	const char* createUsersTableQuery = "CREATE TABLE USERS (USERNAME TEXT PRIMARY KEY , PASSWORD TEXT NOT NULL , EMAIL TEXT NOT NULL);";

	return sqlite3_exec(this->m_db, createUsersTableQuery, nullptr, nullptr, nullptr);
}

const char* SqliteDatabase::constructQuery(SelectQuery query)
{
	std::string queryStr = "SELECT ";

	for (int i = 0; i < query.fields.size(); i++)
	{
		queryStr += query.fields[i];
		if (i < query.fields.size() - 1)
		{
			queryStr += ",";
		}
		queryStr += " ";
	}

	queryStr += std::string("FROM ") +
		query.tables[0] +
		std::string(" ");

	for (int i = 1; i < query.tables.size(); i++)
	{
		queryStr += std::string("INNER JOIN ") +
			query.tables[i] +
			std::string(" ON ") +
			query.joiners[i - 1].first +
			std::string(" = ") +
			query.joiners[i - 1].second +
			std::string(" ");
	}

	queryStr += string("WHERE ");

	for (int i = 0; i < query.conditions.size(); i++)
	{
		queryStr += query.conditions[i].first +
			std::string(" = ") +
			query.conditions[i].second;

		if (i < query.conditions.size() - 1)
		{
			queryStr += " AND ";
		}
	}

	queryStr += ";";

	return queryStr.c_str();
}

const char* SqliteDatabase::constructQuery(InsertQuery query)
{
	std::string queryStr = std::string("INSERT INTO ") +
		query.table +
		std::string(" (");

	if (query.table == "USERS")
	{
		queryStr += "USERNAME , PASSWORD , EMAIL) VALUES (";
	}

	for (int i = 0; i < query.values.size(); i++)
	{
		queryStr += query.values[i];
		if (i < query.values.size() - 1)
		{
			queryStr += " , ";
		}
		else
		{
			queryStr += ");";
		}
	}

	return queryStr.c_str();
}

const char* SqliteDatabase::constructQuery(DeleteQuery query)
{
	std::string queryStr = std::string("DELETE FROM ") +
		query.table +
		std::string(" WHERE ");

	for (int i = 0; i < query.conditions.size(); i++)
	{
		queryStr += query.conditions[i].first +
			std::string(" = ") +
			query.conditions[i].second;

		if (i < query.conditions.size() - 1)
		{
			queryStr += " AND ";
		}
		else
		{
			queryStr += ";";
		}
	}

	return queryStr.c_str();
}

int SqliteDatabase::callback(void* data, int argc, char** argv, char** azColName)
{
	vector<map<string, string>>* pData = (vector<map<string, string>>*)data;
	map<string, string> column;

	for (int i = 0; i < argc; i++)
	{
		column[azColName[i]] = argv[i];
	}

	pData->push_back(column);

	return 0;
}
