#include <map>
#include <vector>
#include <iostream>

#include "StatisticsManager.h"

using std::string;
using std::map;
using std::vector;

/*
	usage: constructor
	in: the database
	out: no
*/
StatisticsManager::StatisticsManager(IDatabase& database) :
	m_database(database)
{
}

/*
	usage: the method gets the statistics of an user
	in: the user
	out: the statistics
*/
Statistics StatisticsManager::getStatistics(LoggedUser loggedUser)
{
	return {
		this->m_database.getPlayerAverageAnswerTime(loggedUser.getUsername()),
		this->m_database.getNumOfCorrectAnswers(loggedUser.getUsername()),
		this->m_database.getNumOfTotalAnswers(loggedUser.getUsername()),
		this->m_database.getNumOfPlayerGames(loggedUser.getUsername()),
		this->m_database.getTopScores(loggedUser.getUsername())
	};
}
