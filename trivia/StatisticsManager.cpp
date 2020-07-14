#include <map>
#include <vector>
#include <iostream>

#include "StatisticsManager.h"
#include "sqliteDataBase.h"

using std::string;
using std::map;
using std::vector;

/*
	usage: the method gets the statistics of an user
	in: the user
	out: the statistics
*/
Statistics StatisticsManager::getStatistics(LoggedUser loggedUser)
{
	return {
		SqliteDatabase::getInstance().getPlayerAverageAnswerTime(loggedUser.getUsername()),
		SqliteDatabase::getInstance().getNumOfCorrectAnswers(loggedUser.getUsername()),
		SqliteDatabase::getInstance().getNumOfTotalAnswers(loggedUser.getUsername()),
		SqliteDatabase::getInstance().getNumOfPlayerGames(loggedUser.getUsername()),
		SqliteDatabase::getInstance().getTopScores(loggedUser.getUsername())
	};
}
