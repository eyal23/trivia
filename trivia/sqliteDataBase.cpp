#include "sqliteDataBase.h"

#include "sqlite3.h"
#include <vector>



bool sqliteData::doesUserExist(string username)
{
	char* sqlStatement = ;

	char* errMessage = nullptr;
	res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
}

bool sqliteData::doesPasswordMatch(string username, string password)
{
	return false;
}

void sqliteData::addNewUser(string username, string password, string email)
{
}
