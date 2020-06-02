#include "Room.h"

Room::Room(RoomData metadata) :
	m_metadata(metadata)
{
}

bool Room::addUser(LoggedUser loggedUser)
{
	if (this->m_metadata.maxPlayers <= this->m_users.size())
	{
		return false;
	}

	for (int i = 0; i < this->m_users.size(); i++)
	{
		if (this->m_users[i].getUsername() == loggedUser.getUsername())
		{
			return false;
		}
	}

	this->m_users.push_back(loggedUser);

	return true;
}

bool Room::removeUser(LoggedUser loggedUser)
{
	for (int i = 0; i < this->m_users.size(); i++)
	{
		if (this->m_users[i].getUsername() == loggedUser.getUsername())
		{
			this->m_users.erase(this->m_users.begin() + i);
			return true;
		}
	}

	return false;
}

vector<string> Room::getAllUsers() const
{
	vector<string> users;

	for (int i = 0; i < this->m_users.size(); i++)
	{
		users.push_back(this->m_users[i].getUsername());
	}

	return users;
}
