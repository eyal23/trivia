#include <vector>

#include "Room.h"

using std::vector;


/*
	usage: constructor
	in: the room's metadata
	out: no
*/
Room::Room(RoomData metadata) :
	m_metadata(metadata)
{
}

/*
	usage: the method adds a new user to the room
	in: the user
	out: if the user was added
*/
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

/*
	usage: the method removes an user from the room 
	in: the user
	out: if the user was removed
*/
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

/*
	usage: the method gets all users in the room
	in: no
	out: all the users in the room
*/
vector<string> Room::getAllUsers() const
{
	vector<string> users;

	for (int i = 0; i < this->m_users.size(); i++)
	{
		users.push_back(this->m_users[i].getUsername());
	}

	return users;
}

/*
	usage: the method gets the room's metadata
	in: no
	out: the room's metadata
*/
const RoomData& Room::getMetadata() const
{
	return this->m_metadata;
}
