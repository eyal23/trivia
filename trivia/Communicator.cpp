#include "Communicator.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>

// using static const instead of macros 
static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

Communicator::Communicator()
{
// notice that we step out to the global namespace
// for the resolution of the function socket
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(_socket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		TRACE("accepting client...");

		SOCKET client_socket = accept(_socket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);
		
		TRACE("Client accepted !");
		// create new thread for client	and detach from it
		std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
		clientThread.detach();
	}                           
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(_socket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

void Communicator::handleNewClient()
{

}