#include "Server.h"
#include <iostream>
#include <thread>

using std::string;
using std::ref;
using std::thread;
using std::cout;
using std::cin;

void communicatorThread(Communicator& communicator)
{
	communicator.startHandleRequests();
}

void Server::run()
{
	thread communicatorThread(communicatorThread, ref(this->m_Communicator));
	communicatorThread.detach();

	string command;
	
	while (command != "EXIT")
	{
		cout << "Enter command: ";
		cin >> command;
	}
}
