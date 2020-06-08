#include <vector>
#include <map>

#include "RoomManager.h"
#include "Room.h"

using std::vector;
using std::map;


/*
	usage: the method creates a new room
	in: the user who creates the room, the metadata
	out: no
*/
void RoomManager::createRoom(LoggedUser loggedUser, RoomData roomData)
{
	roomData.id = this->getNextRoomId();

	this->m_rooms[roomData.id] = Room(roomData);
	this->m_rooms[roomData.id].addUser(loggedUser);
}

/*
	usage: the method deletes a room
	in: the room's id
	out: if the room was deleted
*/
bool RoomManager::deleteRoom(int id)
{
	return this->m_rooms.erase(id);
}

bool RoomManager::joinRoom(int id, LoggedUser loggedUser)
{
	if (this->m_rooms.count(id) == 0)
	{
		return false;
	}

	return this->m_rooms[id].addUser(loggedUser);
}

/*
	usage: the method gets a room's state
	in: the room's id
	out: the room's state
*/
unsigned int RoomManager::getRoomState(int id)
{
	return this->m_rooms[id].getMetadata().isActive;
}

/*
	usage: the method gets all the room
	in: no
	out: all the rooms
*/
vector<RoomData> RoomManager::getRooms() const
{
	vector<RoomData> rooms;
	map<int, Room>::iterator i;

	for (auto const& room : this->m_rooms)
	{
		rooms.push_back(room.second.getMetadata());
	}

	return rooms;
}

vector<string> RoomManager::getPlayersInRoom(int id)
{
	return this->m_rooms[id].getAllUsers();
}

/*
	usage: the method gets the next room id
	in: no
	out: the next room id
*/
int RoomManager::getNextRoomId() const
{
	for (int i = 0; true; i++)
	{
		if (!this->m_rooms.count(i))
		{
			return i;
		}
	}
}
