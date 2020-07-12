#include <io.h>
#include <exception>
#include <vector>
#include <map>
#include <string>

#include "sqliteDataBase.h"
#include "sqlite3.h"
#include "Constants.h"

#define DATABASE_NAME "triviaDB.sqlite"
#define USERS_USERNAME "USERNAME"
#define USERS_PASSWORD "PASSWORD"
#define USERS_EMAIL "EMAIL"
#define QUESTIONS_QUESTION "QUESTION"
#define QUESTIONS_CORRECT_ANSWER "CORRECT_ANSWER"
#define QUESTIONS_INCORRECT_ANSWER_1 "INCORRECT_ANSWER1"
#define QUESTIONS_INCORRECT_ANSWER_2 "INCORRECT_ANSWER2"
#define QUESTIONS_INCORRECT_ANSWER_3 "INCORRECT_ANSWER3"
#define STATISTICS_ID "ID"
#define STATISTICS_USERNAME "USERNAME"
#define STATISTICS_TOTAL_ANSWERS "TOTAL_ANSWERS"
#define STATISTICS_CORRECT_ANSWERS "CORRECT_ANSWERS"
#define STATISTICS_TOTAL_TIME "TOTAL_TIME"

using std::exception;
using std::vector;
using std::map;
using std::stoi;
using std::to_string;


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

/*
	usage: the method gets the average answer time of an user
	in: the username
	out: the average answer time of the user
*/
float SqliteDatabase::getPlayerAverageAnswerTime(string username)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "STATISTICS" },
		{},
		{ string("AVG(") + STATISTICS_TOTAL_TIME + string(") AS AVERAGE_ANSWER_TIME") },
		{
			{ STATISTICS_USERNAME, string("\"") + username + string("\"") }
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	return result.size() > 0 ? stoi(result[0]["AVERAGE_ANSWER_TIME"]) : 0;
}

/*
	usage: the method gets the number of correct answers of an user
	in: the username
	out: the number of correct answers of the user
*/
int SqliteDatabase::getNumOfCorrectAnswers(string username)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "STATISTICS" },
		{},
		{ string("SUM(") + STATISTICS_CORRECT_ANSWERS + string(") AS TOTAL_CORRECT_ANSWERS") },
		{
			{ STATISTICS_USERNAME, string("\"") + username + string("\"") }
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	return result.size() > 0 ? stoi(result[0]["TOTAL_CORRECT_ANSWERS"]) : 0;
}

/*
	usage: the method gets the number of answers of an user
	in: the username
	out: the number of answers of the user
*/
int SqliteDatabase::getNumOfTotalAnswers(string username)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "STATISTICS" },
		{},
		{ string("SUM(") + STATISTICS_TOTAL_ANSWERS + string(") AS TOTAL_TOTAL_ANSWERS") },
		{
			{ STATISTICS_USERNAME, string("\"") + username + string("\"") }
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	return result.size() > 0 ? stoi(result[0]["TOTAL_TOTAL_ANSWERS"]) : 0;
}

/*
	usage: the method gets the number games a player have played
	in: the username
	out: the number games the player have played
*/
int SqliteDatabase::getNumOfPlayerGames(string username)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "STATISTICS" },
		{},
		{ string("COUNT(") + STATISTICS_ID + string(") AS PLAYER_GAMES") },
		{
			{ STATISTICS_USERNAME, string("\"") + username + string("\"") }
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	return result.size() > 0 ? stoi(result[0]["PLAYER_GAMES"]) : 0;
}

/*
	usage: the method gets the top scores of an user
	in: the username
	out: the user's top scores
*/
int* SqliteDatabase::getTopScores(string username)
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "STATISTICS" },
		{},
		{ STATISTICS_CORRECT_ANSWERS, STATISTICS_TOTAL_TIME },
		{
			{ STATISTICS_USERNAME, string("\"") + username + string("\"") }
		}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	int topScores[5] = { 0, 0, 0, 0, 0 };

	for (int i = 0; i < result.size(); i++)
	{
		int currentScore = stoi(result[i][STATISTICS_CORRECT_ANSWERS]) + int(100 / stoi(result[i][STATISTICS_TOTAL_TIME]));

		for (int j = 0; j < 5; j++)
		{
			if (currentScore > topScores[j])
			{
				for (int h = 5; h > j; h--)
				{
					topScores[h] = topScores[h - 1];
				}

				topScores[j] = currentScore;
				break;
			}
		}
	}

	return topScores;
}

void SqliteDatabase::addStatistic(string username, unsigned int totalAnswers, unsigned int correctAnswers, float totalAnswerTime)
{
	InsertQuery query = {
		"STATISTICS",
		{
			string("\"") + username + string("\""),
			to_string(totalAnswers),
			to_string(correctAnswers),
			to_string(totalAnswerTime)
		},
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), nullptr, nullptr, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}
}

vector<Question> SqliteDatabase::getQuestions()
{
	vector<map<string, string>> result;
	SelectQuery query = {
		{ "QUESTIONS" },
		{},
		{ 
			QUESTIONS_QUESTION, 
			QUESTIONS_CORRECT_ANSWER,
			QUESTIONS_INCORRECT_ANSWER_1,
			QUESTIONS_INCORRECT_ANSWER_2,
			QUESTIONS_INCORRECT_ANSWER_3
		},
		{}
	};

	if (sqlite3_exec(this->m_db, SqliteDatabase::constructQuery(query).c_str(), callback, &result, nullptr) != SQLITE_OK)
	{
		throw exception("could'nt access database");
	}

	vector<Question> questions;

	for (int i = 0; i < result.size(); i++)
	{
		questions.push_back(Question(
			result[i][QUESTIONS_QUESTION], 
			{ 
				result[i][QUESTIONS_CORRECT_ANSWER],
				result[i][QUESTIONS_INCORRECT_ANSWER_1], 
				result[i][QUESTIONS_INCORRECT_ANSWER_2], 
				result[i][QUESTIONS_INCORRECT_ANSWER_3] 
			}
		));
	}
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
		"CREATE TABLE QUESTIONS (ID INTEGER PRIMARY KEY AUTOINCREMENT , QUESTION TEXT NOT NULL , CORRECT_ANSWER TEXT NOT NULL , INCORRECT_ANSWER1 TEXT NOT NULL , INCORRECT_ANSWER2 TEXT NOT NULL , INCORRECT_ANSWER3 TEXT NOT NULL);",
		"CREATE TABLE STATISTICS (ID INTEGER PRIMARY KEY AUTOINCREMENT , USERNAME TEXT FOREIGON KEY REFERENCES USERS(USERNAME) , TOTAL_ANSWERS INTEGER NOT NULL , CORRECT_ANSWERS INTEGER NOT NULL , TOTAL_TIME REAL NOT NULL);"
	};

	for (int i = 0; i < tableQueries.size(); i++)
	{
		if (sqlite3_exec(this->m_db, tableQueries[i], nullptr, nullptr, nullptr) != SQLITE_OK)
		{
			true;
		}
	}

	vector<map<const string, const string>> questions = {
		{
			{ QUESTIONS_QUESTION, "\"What did the Spanish autonomous community of Catalonia ban in 2010, that took effect in 2012?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Bullfighting\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Fiestas\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Flamenco\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Mariachi\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"What is the romanized Russian word for 'winter'?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Zima\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Leto\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Vesna\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Osen\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"The term 'scientist' was coined in which year?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"1833\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"1933\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"1942\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"1796\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"The new One World Trade Center in Manhattan, New York City was designed by which architect?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"David Childs\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Bjarke Ingels\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Michael Arad\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Fumihiko Maki\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"Amsterdam Centraal station is twinned with what station?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"London Liverpool Street\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Frankfurt (Main) Hauptbahnhof\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Paris Gare du Nord\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Brussels Midi\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"Where does water from Poland Spring water bottles come from?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Maine, United States\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Hesse, Germany\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Masovia, Poland\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Bavaria, Poland\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"In a 1994 CBS interview, Microsoft co-founder Bill Gates performed what unusual trick on camera?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Jumping over an office chair\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Jumping backwards over a desk\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Standing on his head\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Typing on a keyboard during a handstand\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"What is real haggis made of?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Sheep's Heart, Liver and Lungs\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Sheep's Heart, Kidneys and Lungs\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Sheep's Liver, Kidneys and Eyes\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Whole Sheep\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"Which of these words means 'idle spectator'?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Gongoozler\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Gossypiboma\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Jentacular\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Meupareunia\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"What was the name given to Japanese military dictators who ruled the country through the 12th and 19th Century?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Shogun\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Ninja\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Samurai\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Shinobi\"" }
		}
	};

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
	else if (query.table == "STATISTICS")
	{
		queryStr += "USERNAME , GAME_ID , TOTAL_ANSWERS , CORRECT_ANSWERS , TOTAL_TIME) VALUES (";
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
