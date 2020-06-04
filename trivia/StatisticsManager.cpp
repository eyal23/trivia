#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database) :
	m_database(database)
{
}

Statistics StatisticsManager::getStatistics(LoggedUser loggedUser)
{
	return {
		this->m_database->getPlayerAverageAnswerTime(loggedUser.getUsername()),
		this->m_database->getNumOfCorrectAnswers(loggedUser.getUsername()),
		this->m_database->getNumOfTotalAnswers(loggedUser.getUsername()),
		this->m_database->getNumOfPlayerGames(loggedUser.getUsername())
	};
}
