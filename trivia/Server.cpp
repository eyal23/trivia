#include "Server.h"
#include <iostream>
#include <thread>

using std::string;
using std::thread;
using std::ref;
using std::cout;
using std::cin;

/*
	this function calls the startHandleRequests method 
	from the Communicator class.

	input: the communicator.
	output: none.
*/
void communicatorThread(Communicator& communicator)
{
	communicator.startHandleRequests();
}

/*
	this method starts with creating & detaching a thread that will 
	start the Communicator who will be listening and accepting clients.
	the code steps into a while loop and unless the word exit was not typed in
	then the code keeps on runing.
	
	input: none.
	output: none.
*/
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