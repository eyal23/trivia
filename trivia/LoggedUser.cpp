#include "LoggedUser.h"


/*
	usage: constructor
	in: the username
	out: no
*/
LoggedUser::LoggedUser(const string username) :
	m_username(username)
{
}

/*
	usage: the method gets the user's username
	in:
	out:
*/
string LoggedUser::getUsername() const
{
	return m_username;
}
