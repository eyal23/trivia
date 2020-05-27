#pragma once

#include "IDatabase.h"

class MongoDatabase: public IDatabase
{
public:
	bool doesUserExist(string username) override;
	bool doesPasswordMatch(string username, string password) override;
	void addNewUser(string username, string password, string email) override;
};