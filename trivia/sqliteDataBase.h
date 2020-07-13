#pragma once

#include <iostream>
#include <vector>

#include "sqlite3.h"
#include "Question.h"

using std::string;
using std::vector;
using std::pair;


class SqliteDatabase
{
	typedef struct SelectQuery
	{
		vector<string> tables;
		vector<pair<string, string>> joiners;
		vector<string> fields;
		vector<pair<string, string>> conditions;
	} SelectQuery;

	typedef struct InsertQuery
	{
		string table;
		vector<string> values;
	} InsertQuery;

	typedef struct DeleteQuery
	{
		string table;
		vector<pair<string, string>> conditions;
	} DeleteQuery; 

private:
	sqlite3* m_db;

public:
	static SqliteDatabase& getInstance()
	{
		static SqliteDatabase instance;
		return instance;
	}

	bool doesUserExist(string username);
	bool doesPasswordMatch(string username, string password);
	void addNewUser(string username, string password, string email);
	float getPlayerAverageAnswerTime(string username);
	int getNumOfCorrectAnswers(string username);
	int getNumOfTotalAnswers(string username);
	int getNumOfPlayerGames(string username);
	int* getTopScores(string username);
	void addStatistic(string username, unsigned int totalAnswers, unsigned int correctAnswers, float totalAnswerTime);
	vector<Question> getQuestions();

	SqliteDatabase(SqliteDatabase const&) = delete;
	void operator=(SqliteDatabase const&) = delete;

private:
	SqliteDatabase();
	~SqliteDatabase();

	bool initDatabase();
	static string constructQuery(SelectQuery query);
	static string constructQuery(InsertQuery query);
	static string constructQuery(DeleteQuery query);
	static int callback(void* data, int argc, char** argv, char** azColName);
};