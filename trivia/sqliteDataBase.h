#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

#include <iostream>
#include <string>

using std::string;

class sqliteData: public IDatabase
{
public:
	sqlite3* db;
	int databse = sqlite3_open("example.db", &db);

	bool doesUserExist(string username) override;
	bool doesPasswordMatch(string username, string password) override;
	void addNewUser(string username, string password, string email) override;
};