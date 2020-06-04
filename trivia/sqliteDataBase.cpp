#include <io.h>
#include <exception>
#include <vector>
#include <map>

#include "sqliteDataBase.h"
#include "sqlite3.h"
#include "Constants.h"

#define DATABASE_NAME "triviaDB.sqlite"

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
			{ USERS_USERNAME, string("\"") + username + string("\"") },
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), callback, &result, nullptr) != SQLITE_OK)
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
			{ USERS_USERNAME, string("\"") + username + string("\"") },
			{ USERS_PASSWORD, string("\"") + password + string("\"") }
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), callback, &result, nullptr) != SQLITE_OK)
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
			string("\"") + username + string("\""),
			string("\"") + password + string("\""),
			string("\"") + email + string("\"")
		},
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), nullptr, nullptr, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}
}

float SqliteDatabase::getPlayerAverageAnswerTime(string username)
{
	return 0.0f;
}

int SqliteDatabase::getNumOfCorrectAnswers(string username)
{
	return 0;
}

int SqliteDatabase::getNumOfTotalAnswers(string username)
{
	return 0;
}

int SqliteDatabase::getNumOfPlayerGames(string username)
{
	return 0;
}

int* SqliteDatabase::getTopScores(string username)
{
	return nullptr;
}

/*
	usage: the method initializes the database
	in: no
	out: if the initialization was succesful
*/
bool SqliteDatabase::initDatabase()
{
	const vector<const char*> tableQueries = {
		"CREATE TABLE USERS (USERNAME TEXT PRIMARY KEY , PASSWORD TEXT NOT NULL , EMAIL TEXT NOT NULL);",
		"CREATE TABLE QUESTIONS (ID INTEGER PRIMARY KEY AUTOINCREMENT , QUESTION TEXT NOT NULL , CORRECT_ANSWER TEXT NOT NULL , INCORRECT_ANSWER1 TEXT NOT NULL , INCORRECT_ANSWER2 TEXT NOT NULL , INCORRECT_ANSWER3 TEXT NOT NULL);"
	};

	for (int i = 0; i < tableQueries.size(); i++)
	{
		if (sqlite3_exec(this->m_db, tableQueries[i], nullptr, nullptr, nullptr) != SQLITE_OK)
		{
			true;
		}
	}

	for (int i = 0; i < questions.size(); i++)
	{
		InsertQuery query = {
		"QUESTIONS",
		{
			questions[i][QUESTIONS_QUESTION],
			questions[i][QUESTIONS_CORRECT_ANSWER],
			questions[i][QUESTIONS_INCORRECT_ANSWER_1],
			questions[i][QUESTIONS_INCORRECT_ANSWER_2],
			questions[i][QUESTIONS_INCORRECT_ANSWER_3]
		},
		};

		if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), nullptr, nullptr, nullptr) != SQLITE_OK)
		{
			true;
		}
	}

	return false;
}

/*
	usage: the method constructs a select query
	in: the select query's parameters
	out: the select query
*/
string SqliteDatabase::constructQuery(SelectQuery query)
{
	string queryStr = "SELECT ";

	for (int i = 0; i < query.fields.size(); i++)
	{
		queryStr += query.fields[i];
		if (i < query.fields.size() - 1)
		{
			queryStr += ",";
		}
		queryStr += " ";
	}

	queryStr += string("FROM ") +
		query.tables[0] +
		string(" ");

	for (int i = 1; i < query.tables.size(); i++)
	{
		queryStr += std::string("INNER JOIN ") +
			query.tables[i] +
			string(" ON ") +
			query.joiners[i - 1].first +
			string(" = ") +
			query.joiners[i - 1].second +
			string(" ");
	}

	queryStr += string("WHERE ");

	for (int i = 0; i < query.conditions.size(); i++)
	{
		queryStr += query.conditions[i].first +
			string(" = ") +
			query.conditions[i].second;

		if (i < query.conditions.size() - 1)
		{
			queryStr += " AND ";
		}
	}

	queryStr += ";";

	return queryStr;
}

/*
	usage: the method constructs an insert query
	in: the insert query's parameters
	out: the insert query
*/
string SqliteDatabase::constructQuery(InsertQuery query)
{
	string queryStr = string("INSERT INTO ") +
		query.table +
		string(" (");

	if (query.table == "USERS")
	{
		queryStr += "USERNAME , PASSWORD , EMAIL) VALUES (";
	}
	else if (query.table == "QUESTIONS")
	{
		queryStr += "QUESTION , CORRECT_ANSWER , INCORRECT_ANSWER1 , INCORRECT_ANSWER2 , INCORRECT_ANSWER3) VALUES (";
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

	return queryStr;
}

/*
	usage: the method constructs a delete query
	in: the delete query's parameters
	out: the delete query
*/
string SqliteDatabase::constructQuery(DeleteQuery query)
{
	string queryStr = string("DELETE FROM ") +
		query.table +
		string(" WHERE ");

	for (int i = 0; i < query.conditions.size(); i++)
	{
		queryStr += query.conditions[i].first +
			string(" = ") +
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

	return queryStr;
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
