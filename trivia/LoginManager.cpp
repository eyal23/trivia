#include "LoginManager.h"
#include "LoggedUser.h"
#include "IDatabase.h"


/*
	usage: constructor
	in: the database
	out: no
*/
LoginManager::LoginManager(IDatabase& database) :
	m_database(database)
{
}

/*
	usage: the method tries to sign up a user into the db
	in: the username, the password, the email
	out: if the signup was succesful
*/
bool LoginManager::signup(const string username, const string password, const string email) const
{
	if (this->m_database.doesUserExist(username))
	{
		return false;
	}

	this->m_database.addNewUser(username, password, email);

	return true;
}

/*
	usage: the method tries to login into user's account
	in: the username, the password
	out: if the login was succesful
*/
bool LoginManager::login(const string username, const string password)
{
	if (!this->m_database.doesPasswordMatch(username, password))
	{
		return false;
	}

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
