#include <io.h>
#include <exception>
#include <vector>
#include <map>

#include "sqliteDataBase.h"
#include "sqlite3.h"

#define DATABASE_NAME "triviaDB.sqlite"
#define USERS_USERNAME "USERNAME"
#define USERS_PASSWORD "PASSWORD"
#define USERS_EMAIL "EMAIL"

using std::exception;
using std::vector;
using std::map;


/*
	usage: constructor
	in: no
	out: no
*/
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

/*
	usage: destructor
	in: no
	out: no
*/
SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(this->m_db);
}

/*
	usage: the method checks if a user exists in the database
	in: the username
	out: if the user exists in the database
*/
bool SqliteDatabase::doesUserExist(string username)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "USERS" },
		{},
		{ USERS_USERNAME },
		{
			{ USERS_USERNAME, username },
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	return result.size() != 0;
}

/*
	usage: the method checks if an username and password match
	in: the username, the password
	out: if the username and password match
*/
bool SqliteDatabase::doesPasswordMatch(string username, string password)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "USERS" },
		{},
		{ USERS_USERNAME },
		{
			{ USERS_USERNAME, username },
			{ USERS_PASSWORD, password }
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	return result.size() != 0;
}

/*
	usage: the method adds a new user to the database
	in: the username, the password, the email
	out: no
*/
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

/*
	usage: the method initializes the database
	in: no
	out: if the initialization was succesful
*/
bool SqliteDatabase::initDatabase()
{
	const char* createUsersTableQuery = "CREATE TABLE USERS (USERNAME TEXT PRIMARY KEY , PASSWORD TEXT NOT NULL , EMAIL TEXT NOT NULL);";

	return sqlite3_exec(this->m_db, createUsersTableQuery, nullptr, nullptr, nullptr);
}

/*
	usage: the method constructs a select query
	in: the select query's parameters
	out: the select query
*/
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

/*
	usage: the method constructs an insert query
	in: the insert query's parameters
	out: the insert query
*/
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

/*
	usage: the method constructs a delete query
	in: the delete query's parameters
	out: the delete query
*/
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

/*
	usage: callback function for results from the database
	in: place to save the results, how many fields are there in the result, the fields, the values of the fields
	out: 0
*/
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
