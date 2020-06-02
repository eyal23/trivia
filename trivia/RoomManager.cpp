#include "RoomManager.h"
#include "Room.h"

void RoomManager::createRoom(LoggedUser loggedUser, RoomData roomData)
{
	roomData.id = this->getNextRoomId();

	this->m_rooms[roomData.id] = Room(roomData);
	this->m_rooms[roomData.id].addUser(loggedUser);
}

bool RoomManager::deleteRoom(int id)
{
	return this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	return this->m_rooms[id].getMetadata().isActive;
}

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
