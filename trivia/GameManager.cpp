#include "GameManager.h"
#include "sqliteDataBase.h"

using std::lock_guard;


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

	lock_guard<mutex> guard(this->m_gamesMutex);
	this->m_games[id] = Game(players, questions);

	return id;
}

void GameManager::deleteGame(unsigned int gameId)
{
	this->m_gamesMutex.lock();
	vector<PlayerResults> gameResults = this->m_games[gameId].getGameResults();
	this->m_gamesMutex.unlock();

	for (int i = 0; i < gameResults.size(); i++)
	{
		 SqliteDatabase::getInstance().addStatistic(gameResults[i].username, gameResults[i].correctAnswersCount + gameResults[i].wrongAnswersCount, gameResults[i].correctAnswersCount, gameResults[i].averageAnswerTime * (gameResults[i].correctAnswersCount + gameResults[i].wrongAnswersCount));
	}

	this->m_gamesMutex.lock();
	this->m_games.erase(gameId);
	this->m_gamesMutex.unlock();
}

Game& GameManager::operator[](unsigned int id)
{
	lock_guard<mutex> guard(this->m_gamesMutex);
    return this->m_games[id];
}

unsigned int GameManager::getNextGameId()
{
	lock_guard<mutex> guard(this->m_gamesMutex);

	for (int i = 0; true; i++)
	{
		if (!this->m_games.count(i))
		{
			return i;
		}
	}
}
