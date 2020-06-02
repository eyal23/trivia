#pragma once

#include <iostream>
#include <list>

using std::string;
using std::list;

class IDatabase
{
public:
	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string username, string password) = 0;
	virtual void addNewUser(string username, string password, string email) = 0;
	virtual float getPlayerAverageAnswerTime(string) = 0;
	virtual int getNumOfCorrectAnswers(string) = 0;
	virtual int getNumOfTotalAnswers(string) = 0;
	virtual int getNumOfPlayerGames(string) = 0;
};

