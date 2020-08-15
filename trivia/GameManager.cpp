#include <mutex>
#include "GameManager.h"
#include "sqliteDataBase.h"

using std::mutex;
using std::lock_guard;

static mutex gamesMutex;


unsigned int GameManager::createGame(Room room)
{
	vector<string> usernames = room.getAllUsers();
	vector<LoggedUser> players;
	vector<Question> questions;

	for (int i = 0; i < usernames.size(); i++)
	{
		players.push_back(LoggedUser(usernames[i]));
	}

	unsigned int id = this->getNextGameId();

	lock_guard<mutex> guard(gamesMutex);
	this->m_games[id] = Game(players, questions);

	return id;
}

void GameManager::deleteGame(unsigned int gameId)
{
	gamesMutex.lock();
	vector<PlayerResults> gameResults = this->m_games[gameId].getGameResults();
	gamesMutex.unlock();

	for (int i = 0; i < gameResults.size(); i++)
	{
		 SqliteDatabase::getInstance().addStatistic(gameResults[i].username, gameResults[i].correctAnswersCount + gameResults[i].wrongAnswersCount, gameResults[i].correctAnswersCount, gameResults[i].averageAnswerTime * (gameResults[i].correctAnswersCount + gameResults[i].wrongAnswersCount));
	}

	gamesMutex.lock();
	this->m_games.erase(gameId);
	gamesMutex.unlock();
}

Game& GameManager::operator[](unsigned int id)
{
	lock_guard<mutex> guard(gamesMutex);
    return this->m_games[id];
}

unsigned int GameManager::getNextGameId()
{
	lock_guard<mutex> guard(gamesMutex);

	for (int i = 0; true; i++)
	{
		if (!this->m_games.count(i))
		{
			return i;
		}
	}
}
