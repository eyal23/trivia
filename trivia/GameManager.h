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

	unsigned int createGame(Room room);
	void deleteGame(unsigned int gameId);

	Game& operator[](unsigned int id);

private:
	unsigned int getNextGameId() const;
};

