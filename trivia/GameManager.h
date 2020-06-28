#pragma once

#include <map>

#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include "JsonResponsePacketSerializer.h"

using std::map;


class GameManager
{
private:
	IDatabase& m_database;
	map<unsigned int, Game> m_games;

public:
	GameManager(IDatabase& database);

	Game createGame(Room room);
	void deleteGame(Game game);

	Game& operator[](unsigned int id);
};

