#include "GameManager.h"

GameManager::GameManager(IDatabase& database) :
    m_database(database)
{
}

Game GameManager::createGame(Room room)
{
    return Game(vector<LoggedUser>());
}

void GameManager::deleteGame(Game game)
{
}
