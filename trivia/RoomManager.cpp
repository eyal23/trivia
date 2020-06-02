#include "RoomManager.h"

RoomManager::RoomManager(IDatabase* database)
{
}

bool RoomManager::createRoom(LoggedUser, RoomData)
{
	return false;
}

bool RoomManager::deleteRoom(int id)
{
	return false;
}

unsigned int RoomManager::getRoomState(int id) const
{
	return 0;
}

vector<RoomData> RoomManager::getRooms() const
{
	return vector<RoomData>();
}
