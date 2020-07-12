#pragma once

#include "LoggedUser.h"


typedef struct Statistics
{
	float averageAnswerTime;
	int numberOfCorrectAnswers;
	int numberOfTotalAnswers;
	int numberOfPlayerGames;
	int* topScores;
} Statistics;

class StatisticsManager
{
public:
	static StatisticsManager& getInstance()
	{
		static StatisticsManager instance;
		return instance;
	}

	Statistics getStatistics(LoggedUser loggedUser);

	StatisticsManager(StatisticsManager const&) = delete;
	void operator=(StatisticsManager const&) = delete;

private:
	StatisticsManager() {}
};

