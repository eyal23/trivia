#pragma once

#include <map>
#include <vector>

#include "Room.h"
#include "IDatabase.h"
#include "LoggedUser.h"

using std::map;
using std::vector;

class RoomManager
{
private:
	map<int, Room> m_rooms;
	IDatabase* m_database;

public:
	RoomManager(IDatabase* database);

	bool createRoom(LoggedUser, RoomData);
	bool deleteRoom(int id);
	unsigned int getRoomState(int id) const;
	vector<RoomData> getRooms() const;
};

