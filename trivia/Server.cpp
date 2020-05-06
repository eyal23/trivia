#include "Server.h"
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
}
