#pragma once

#include <iostream>
#include <vector>

#include "IDatabase.h"
#include "sqlite3.h"

using std::string;
using std::vector;
using std::pair;


class SqliteDatabase: public IDatabase
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
	SqliteDatabase();
	~SqliteDatabase();

	bool doesUserExist(string username) override;
	bool doesPasswordMatch(string username, string password) override;
	void addNewUser(string username, string password, string email) override;

private:
	bool initDatabase();
	static string constructQuery(SelectQuery query);
	static string constructQuery(InsertQuery query);
	static string constructQuery(DeleteQuery query);
	static int callback(void* data, int argc, char** argv, char** azColName);
};