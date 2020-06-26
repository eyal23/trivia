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

Question GameManager::getUserQuestion(LoggedUser loggedUser)
{
    return Question();
}

void GameManager::submitAnswer(LoggedUser loggedUser, unsigned int answerId)
{
}

GameData GameManager::getGameResults(LoggedUser loggedUser)
{
    return GameData();
}
