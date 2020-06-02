#pragma once

#include "IDatabase.h"

class StatisticsManager
{
private:
	IDatabase* m_database;

public:
	StatisticsManager(IDatabase* database);

	void getStatistics();
};

