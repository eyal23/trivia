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
	unsigned int maxPlayers;
	unsigned int timePerQuestion;
	unsigned int questionsCount;
	bool isActive;
	bool isOpen;
} RoomData;

class Room
{
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;

public:
	Room();
	Room(RoomData metadata);

	bool addUser(LoggedUser loggedUser);
	bool removeUser(LoggedUser loggedUser);
	vector<string> getAllUsers() const;
	const RoomData& getMetadata() const;
	void activateRoom();
	void closeRoom();
};

