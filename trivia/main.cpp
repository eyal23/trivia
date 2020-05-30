#include "Server.h"
#include "WSAInitializer.h"
#include "MongoDatabase.h"

int main()
{
	try
	{
		WSAInitializer wsaInit;
		MongoDatabase mongoDatabase;
		Server server(&mongoDatabase);

		server.run();
	}
	catch (const std::exception& e) 
	{
		e.what();
	}

	return 0;
}