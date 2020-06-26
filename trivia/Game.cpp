#include "Game.h"

Game::Game(vector<LoggedUser> loggedUsers)
{
}

Question Game::getQuestionForUser(LoggedUser loggedUser)
{
    return Question(string(), vector<string>());
}

void Game::submitAnswer(LoggedUser loggedUser, unsigned int answerId)
{
}

void Game::removePlayer(LoggedUser loggedUser)
{
}

GameData Game::getUserGameData(LoggedUser loggedUser)
{
    return GameData();
}
