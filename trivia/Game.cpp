#include "Game.h"

Game::Game(vector<LoggedUser> players, vector<Question> questions) :
	m_questions(questions)
{
	for (int i = 0; i < players.size(); i++)
	{
		this->m_players[players[i]] = GameData({
			this->m_questions[0],
			0,
			0,
			0
		});
	}
}

Game::Game()
{
}

Question Game::getQuestionForUser(LoggedUser loggedUser)
{
    return this->m_players[loggedUser].currentQuestion;
}

void Game::submitAnswer(LoggedUser loggedUser, unsigned int answerId, float answerTime)
{
	if (this->m_players[loggedUser].currentQuestion.getCorrectAnswer() == this->m_players[loggedUser].currentQuestion.getAnswers()[answerId])
	{
		this->m_players[loggedUser].correctAnswersCount++;
	}
	else
	{
		this->m_players[loggedUser].wrongAnswersCount++;
	}

	this->m_players[loggedUser].totalAnswerTime += answerTime;
}

void Game::removePlayer(LoggedUser loggedUser)
{
	this->m_players.erase(loggedUser);
}

vector<PlayerResults> Game::getGameResults()
{
	vector<PlayerResults> gameResults;

	for (map<LoggedUser, GameData>::iterator player = this->m_players.begin(); player != this->m_players.end(); ++player)
	{
		gameResults.push_back(PlayerResults({ player->first.getUsername(), player->second.correctAnswersCount, player->second.wrongAnswersCount, player->second.totalAnswerTime / (player->second.correctAnswersCount + player->second.wrongAnswersCount) }));
	}

	return gameResults;
}
