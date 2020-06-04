#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"

typedef struct Statistics
{
	float averageAnswerTime;
	int numberOfCorrectAnswers;
	int numberOfTotalAnswers;
	int numberOfPlayerGames;
} Statistics;

class StatisticsManager
{
private:
	IDatabase* m_database;

public:
	StatisticsManager(IDatabase* database);

	Statistics getStatistics(LoggedUser loggedUser);
};

