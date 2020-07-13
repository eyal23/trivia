#pragma once

#include <vector>
#include <mutex>

#include "LoggedUser.h"

using std::vector;
using std::string;
using std::mutex;

class LoginManager
{
private:
	vector<LoggedUser> m_loggedUsers;
	mutex m_loggedUsersMutex;

public:
	static LoginManager& getInstance()
	{
		static LoginManager instance;
		return instance;
	}

	bool signup(const string username, const string password, const string email) const;
	bool login(const string username, const string password);
	bool logout(const string username);

	LoginManager(LoginManager const&) = delete;
	void operator=(LoginManager const&) = delete;

private:
	LoginManager() {}
};