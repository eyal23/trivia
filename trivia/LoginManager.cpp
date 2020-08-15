#include <mutex>

#include "LoginManager.h"
#include "LoggedUser.h"
#include "sqliteDataBase.h"

using std::mutex;
using std::lock_guard;

static mutex loggedUsersMutex;


/*
	usage: the method tries to sign up a user into the db
	in: the username, the password, the email
	out: if the signup was succesful
*/
bool LoginManager::signup(const string username, const string password, const string email) const
{
	if (SqliteDatabase::getInstance().doesUserExist(username))
	{
		return false;
	}

	SqliteDatabase::getInstance().addNewUser(username, password, email);

	return true;
}

/*
	usage: the method tries to login into user's account
	in: the username, the password
	out: if the login was succesful
*/
bool LoginManager::login(const string username, const string password)
{
	if (!SqliteDatabase::getInstance().doesPasswordMatch(username, password))
	{
		return false;
	}

	lock_guard<mutex> guard(loggedUsersMutex);

	for (int i = 0; i < this->m_loggedUsers.size(); i++)
	{
		if (this->m_loggedUsers[i].getUsername() == username)
		{
			return false;
		}
	}

	this->m_loggedUsers.push_back(LoggedUser(username));

	return true;
}

/*
	usage: the method tries to logout from a user's account
	in: the username
	out: if the logout was succeful
*/
bool LoginManager::logout(const string username)
{
	lock_guard<mutex> guard(loggedUsersMutex);

	for (int i = 0; i < this->m_loggedUsers.size(); i++)
	{
		if (this->m_loggedUsers[i].getUsername() == username)
		{
			this->m_loggedUsers.erase(this->m_loggedUsers.begin() + i);
			return true;
		}
	}

	return false;
}
