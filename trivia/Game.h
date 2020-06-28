#pragma once

#include <vector>
#include <map>

#include "Question.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"

using std::map;
using std::vector;


typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswersCount;
	unsigned int wrongAnswersCount;
	unsigned int averageAnswerTime;
} GameData;

class Game
{
private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;

public:
	Game(vector<LoggedUser> loggedUsers);
	Game();

	Question getQuestionForUser(LoggedUser loggedUser);
	void submitAnswer(LoggedUser loggedUser, unsigned int answerId);
	void removePlayer(LoggedUser loggedUser);
	vector<PlayerResults> getGameResults();
};

