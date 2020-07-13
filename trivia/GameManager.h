#pragma once

#include <map>
#include <vector>
#include <mutex>

#include "Game.h"
#include "Room.h"

using std::map;
using std::vector;
using std::mutex;


class GameManager
{
private:
	map<unsigned int, Game> m_games;
	mutex m_gamesMutex;

public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}

	unsigned int createGame(Room room);
	void deleteGame(unsigned int gameId);

	Game& operator[](unsigned int id);

	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;

private:
	GameManager() {}

	unsigned int getNextGameId();
};

