#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <mutex>

#include "Room.h"
#include "LoggedUser.h"

using std::map;
using std::vector;
using std::string;
using std::mutex;


typedef struct RoomState
{
	bool isRoomOpen;
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionsCount;
	unsigned int answerTimeout;
} RoomState;

class RoomManager
{
private:
	map<int, Room> m_rooms;
	mutex m_roomsMutex;

public:
	static RoomManager& getInstance()
	{
		static RoomManager instance;
		return instance;
	}

	int createRoom(LoggedUser loggedUser, RoomData roomData);
	void closeRoom(int id);
	bool tryDeleteRoom(int id, LoggedUser loggedUser);
	bool joinRoom(int id, LoggedUser loggedUser);
	RoomState getRoomState(int id);
	vector<RoomData> getRooms();
	vector<string> getPlayersInRoom(int id);
	bool isRoomOpen(int id);

	Room operator[](int id);

	RoomManager(RoomManager const&) = delete;
	void operator=(RoomManager const&) = delete;

private:
	RoomManager() {}

	int getNextRoomId();
};

