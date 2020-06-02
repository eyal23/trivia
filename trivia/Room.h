#pragma once

#include <iostream>
#include <vector>

#include "LoggedUser.h"

using std::string;
using std::vector;

typedef struct RoomData
{
	unsigned int id;
	string name;
	int maxPlayers;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;

class Room
{
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;

public:
	Room(RoomData metadata);

	bool addUser(LoggedUser);
	bool removeUser(LoggedUser);
	vector<string> getAllUsers() const;
};

