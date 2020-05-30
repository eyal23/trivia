#include "LoginManager.h"
#include "LoggedUser.h"
#include "IDatabase.h"

bool LoginManager::signup(string username, string password, string email)
{
	if (!this->m_database->doesUserExist(username))
	{
		return false;
	}

	this->m_database->addNewUser(username, password, email);

	return true;
}

bool LoginManager::login(string username, string password)
{
	if (!this->m_database->doesPasswordMatch(username, password))
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

bool LoginManager::logout(string username)
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
