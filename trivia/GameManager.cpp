#include "GameManager.h"


GameManager::GameManager(IDatabase& database) :
    m_database(database)
{
}

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

	this->m_games[id] = Game(players, questions);

	return id;
}

void GameManager::deleteGame(unsigned int gameId)
{
	this->m_games.erase(gameId);
}

Game& GameManager::operator[](unsigned int id)
{
    return this->m_games[id];
}

unsigned int GameManager::getNextGameId() const
{
	for (int i = 0; true; i++)
	{
		if (!this->m_games.count(i))
		{
			return i;
		}
	}
}
