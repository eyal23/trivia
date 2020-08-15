#include <exception>

#include "Server.h"
#include "WSAInitializer.h"

using std::exception;


int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server::getInstance().run();
	}
	catch (const std::exception& e)
	{
		e.what();
	}

	return 0;
}