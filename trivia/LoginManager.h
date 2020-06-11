#pragma once

#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

using std::vector;
using std::string;

class LoginManager
{
private:
	IDatabase& m_database;
	vector<LoggedUser> m_loggedUsers;

public:
	LoginManager(IDatabase& database);

	bool signup(const string username, const string password, const string email) const;
	bool login(const string username, const string password);
	bool logout(const string username);
};