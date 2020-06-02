#pragma once

#include <map>
#include <vector>

#include "Room.h"
#include "LoggedUser.h"

using std::map;
using std::vector;

class RoomManager
{
private:
	map<int, Room> m_rooms;

public:
	void createRoom(LoggedUser loggedUser, RoomData roomData);
	bool deleteRoom(int id);
	unsigned int getRoomState(int id);
	vector<RoomData> getRooms() const;

private:
	int getNextRoomId() const;
};

