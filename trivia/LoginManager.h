#pragma once

#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

using std::vector;
using std::string;

class LoginManager
{
private:
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;

public:
	bool signup(string username, string password, string email);
	bool login(string username, string password);
	bool logout(string username);
};