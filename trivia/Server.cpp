#include <iostream>
#include <thread>

#include "Server.h"
#include "Communicator.h"

using std::string;
using std::thread;
using std::ref;
using std::cout;
using std::cin;


/*
	usage: the function calls the startHandleRequests method from the Communicator class
	input: the communicator
	output: no
*/
void communicatorThread()
{
	Communicator::getInstance().startHandleRequests();
}

/*
	usage: the method starts the server
	input: no
	output: no
*/
void Server::run()
{
	thread communicatorThread(communicatorThread);
	communicatorThread.detach();

	string command;
	
	while (command != "EXIT")
	{
		cout << "Enter command: ";
		cin >> command;
	}
}