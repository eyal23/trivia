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
	Question currentQuestion = Question(string(), vector<string>());
	unsigned int correctAnswersCount;
	unsigned int wrongAnswersCount;
	float totalAnswerTime;
} GameData;

class Game
{
private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;

public:
	Game(vector<LoggedUser> players, vector<Question> questions);
	Game();

	Question getQuestionForUser(LoggedUser loggedUser);
	void submitAnswer(LoggedUser loggedUser, unsigned int answerId, float answerTime);
	void removePlayer(LoggedUser loggedUser);
	vector<PlayerResults> getGameResults();
};

