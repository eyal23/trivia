#include "Server.h"
<<<<<<< HEAD

void Server::run()
{
=======
#include <thread>

void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests);
	t_connector.detach();

	std::string exitCommand;
	
	while (true)
	{
		std::cin >> exitCommand;

		if (exitCommand == "EXIT")
		{
			std::exit(0);
		}
	}
>>>>>>> d0b5f8afc1ca5f91675391fca373e65860b8f016
}
