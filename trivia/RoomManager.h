#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "Room.h"
#include "LoggedUser.h"

using std::map;
using std::vector;
using std::string;


typedef struct RoomState
{
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionsCount;
	unsigned int answerTimeout;
} RoomState;

class RoomManager
{
private:
	map<int, Room> m_rooms;

public:
	int createRoom(LoggedUser loggedUser, RoomData roomData);
	bool deleteRoom(int id);
	bool joinRoom(int id, LoggedUser loggedUser);
	RoomState getRoomState(int id);
	vector<RoomData> getRooms() const;
	vector<string> getPlayersInRoom(int id);
	bool doesRoomExist(int id) const;

	Room operator[](int id);

private:
	int getNextRoomId() const;
};

