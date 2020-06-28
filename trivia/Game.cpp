#include "Game.h"

Game::Game(vector<LoggedUser> loggedUsers)
{
}

Game::Game()
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

vector<PlayerResults> Game::getGameResults()
{
    return vector<PlayerResults>();
}
