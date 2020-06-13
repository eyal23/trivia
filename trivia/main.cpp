#include "Server.h"
#include "WSAInitializer.h"
#include "SqliteDatabase.h"

int main()
{
	try
	{
		WSAInitializer wsaInit;
		SqliteDatabase sqliteDatabase;
		Server server(sqliteDatabase);

		server.run();
	}
	catch (const std::exception& e)
	{
		e.what();
	}

	return 0;
}