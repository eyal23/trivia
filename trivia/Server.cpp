#include <iostream>
#include <thread>

#include "Server.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

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
	usage: constructor
	in: the database
	out: no
*/
Server::Server(IDatabase* database) :
	m_database(database), m_handlerFactory(RequestHandlerFactory(database)), m_communicator(Communicator(this->m_handlerFactory))
{
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
	thread communicatorThread(communicatorThread, ref(this->m_communicator));
	communicatorThread.detach();

	string command;
	
	while (command != "EXIT")
	{
		cout << "Enter command: ";
		cin >> command;
	}
}