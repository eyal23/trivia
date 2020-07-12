#pragma once

#include <iostream>
#include <vector>
#include <map>

using std::string;
using std::map;
using std::vector;

class IDatabase
{
public:
	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string username, string password) = 0;
	virtual void addNewUser(string username, string password, string email) = 0;
	virtual float getPlayerAverageAnswerTime(string username) = 0;
	virtual int getNumOfCorrectAnswers(string username) = 0;
	virtual int getNumOfTotalAnswers(string username) = 0;
	virtual int getNumOfPlayerGames(string username) = 0;
	virtual int* getTopScores(string username) = 0;
	virtual void addStatistic(string username, unsigned int totalAnswers, unsigned int correctAnswers, float totalAnswerTime) = 0;
};

