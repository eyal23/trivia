#include <vector>
#include <map>
#include <mutex>

#include "RoomManager.h"
#include "Room.h"

using std::vector;
using std::map;
using std::mutex;
using std::lock_guard;

static mutex roomsMutex;


/*
	usage: the method creates a new room
	in: the user who creates the room, the metadata
	out: the new room's id
*/
int RoomManager::createRoom(LoggedUser loggedUser, RoomData roomData)
{
	roomData.id = this->getNextRoomId();

	roomsMutex.lock();
	this->m_rooms[roomData.id] = Room(roomData);
	this->m_rooms[roomData.id].addUser(loggedUser);
	roomsMutex.unlock();

	return roomData.id;
}

/*
	usage: the method closes a room
	in: the room id
	out: no
*/
void RoomManager::closeRoom(int id)
{
	roomsMutex.lock();
	this->m_rooms[id].closeRoom();
	roomsMutex.unlock();
}

/*
	usage: the method deletes a room
	in: the room's id
	out: if the room was deleted
*/
bool RoomManager::tryDeleteRoom(int id, LoggedUser loggedUser)
{
	lock_guard<mutex> guard(roomsMutex);

	this->m_rooms[id].removeUser(loggedUser);

	if (this->m_rooms[id].getAllUsers().size() == 0)
	{
		this->m_rooms.erase(id);
		return true;
	}

	return false;
}

/*
	usage: the method joins a user to a room
	in: the room's id, the logged user
	out: if the user was joined
*/
bool RoomManager::joinRoom(int id, LoggedUser loggedUser)
{
	lock_guard<mutex> guard(roomsMutex);

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
RoomState RoomManager::getRoomState(int id)
{
	lock_guard<mutex> guard(roomsMutex);
	RoomData metadata = this->m_rooms[id].getMetadata();

	return {
		metadata.isOpen,
		metadata.isActive,
		this->m_rooms[id].getAllUsers(),
		metadata.questionsCount,
		metadata.timePerQuestion
	};
}

/*
	usage: the method gets all the room
	in: no
	out: all the rooms
*/
vector<RoomData> RoomManager::getRooms()
{
	vector<RoomData> rooms;
	map<int, Room>::iterator i;

	lock_guard<mutex> guard(roomsMutex);

	for (auto const& room : this->m_rooms)
	{
		rooms.push_back(room.second.getMetadata());
	}

	return rooms;
}

/*
	usage: the method gets all players in a room
	in: the room's id
	out: all players in the room
*/
vector<string> RoomManager::getPlayersInRoom(int id)
{
	lock_guard<mutex> guard(roomsMutex);
	return this->m_rooms[id].getAllUsers();
}

/*
	usage: the method checks if a room is open
	in: the room id
	out: if the room is open
*/
bool RoomManager::isRoomOpen(int id)
{
	lock_guard<mutex> guard(roomsMutex);
	return this->m_rooms[id].getMetadata().isOpen;
}

/*
	usage: the method gets a room
	in: the room id
	out: the room
*/
Room RoomManager::operator[](int id)
{
	lock_guard<mutex> guard(roomsMutex);
	return this->m_rooms[id];
}

/*
	usage: the method gets the next room id
	in: no
	out: the next room id
*/
int RoomManager::getNextRoomId()
{
	lock_guard<mutex> guard(roomsMutex);
	for (int i = 0; true; i++)
	{
		if (!this->m_rooms.count(i))
		{
			return i;
		}
	}
}
