#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "Room.h"
#include "LoggedUser.h"

using std::map;
using std::vector;
using std::string;

class RoomManager
{
private:
	map<int, Room> m_rooms;

public:
	void createRoom(LoggedUser loggedUser, RoomData roomData);
	bool deleteRoom(int id);
	bool joinRoom(int id, LoggedUser loggedUser);
	unsigned int getRoomState(int id);
	vector<RoomData> getRooms() const;
	vector<string> getPlayersInRoom(int id);

private:
	int getNextRoomId() const;
};

