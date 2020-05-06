#include "Server.h"
#include <iostream>
#include <thread>

void communicatorThread(Communicator& communicator)
{
	communicator.startHandleRequests();
}

void Server::run()
{
	std::thread t_connector(communicatorThread, std::ref(this->m_Communicator));
	t_connector.detach();

	std::string exitCommand;
	
	while (exitCommand != "EXIT")
	{
		std::cin >> exitCommand;
	}
}
