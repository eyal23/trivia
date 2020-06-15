#pragma once

#include <vector>

#include "IDatabase.h"
#include "Game.h"
#include "Room.h"

using std::vector;


class GameManager
{
private:
	IDatabase& m_database;
	vector<Game> m_games;

public:
	GameManager(IDatabase& database);

	Game createGame(Room room);
	void deleteGame(Game game);
};

