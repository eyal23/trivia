#include "Server.h"
#include "WSAInitializer.h"

int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server server;

		server.run();
	}
	catch (const std::exception& e) 
	{
		e.what();
	}

	return 0;
}