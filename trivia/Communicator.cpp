#include <iostream>
#include <exception>
#include <thread>
#include <vector>

#include "Communicator.h"
#include "IRequestHandler.h"

#define MAX_BYTES_AMOUNT 1024

using std::exception;
using std::thread;
using std::string;
using std::cout;
using std::endl;
using std::ref;
using std::vector;

static const unsigned short PORT = 8826;
static const unsigned int INTERFACE = 0;


/*
	usage: constructor
	in: the handler factory
	out: no
*/
Communicator::Communicator()
{
	this->_listeningSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->_listeningSocket == INVALID_SOCKET)
	{
		throw exception(__FUNCTION__ " - socket");
	}
}

/*
	usage: destructor
	in: no
	out: no
*/
Communicator::~Communicator()
{
	try
	{
		::closesocket(this->_listeningSocket);
	}
	catch (...) {}
}

/*
	usage: the thread handles with a specific client's requests
	input: the communicator, the client socket
	output: no
*/
void clientThread(SOCKET clientSocket)
{
	while (true)
	{
		IRequestHandler* requestHandler = Communicator::getInstance()[clientSocket];
		vector<uint8_t> buffer(MAX_BYTES_AMOUNT + 1);

		if (recv(clientSocket, (char*)buffer.data(), MAX_BYTES_AMOUNT, 0) == INVALID_SOCKET)
		{
			delete Communicator::getInstance()[clientSocket];
			Communicator::getInstance().removeClient(clientSocket);
			break;
		}

		RequestInfo requestInfo = { (MessageCode)buffer[0], buffer };
		RequestResult requestResult = requestHandler->handleRequest(requestInfo);

		if (send(clientSocket, (char*)requestResult.buffer.data(), requestResult.buffer.size(), 0) == INVALID_SOCKET)
		{
			delete Communicator::getInstance()[clientSocket];
			Communicator::getInstance().removeClient(clientSocket);
			break;
		}

		if (requestResult.newHandler == nullptr)
		{
			Communicator::getInstance()[clientSocket];
			Communicator::getInstance().removeClient(clientSocket);
			break;
		}

		if (Communicator::getInstance()[clientSocket] != requestResult.newHandler)
		{
			delete Communicator::getInstance()[clientSocket];
		}
		
		Communicator::getInstance()[clientSocket] = requestResult.newHandler;
	}
}

/*
	usage: the method starts the handle-requests cicle
	input: no
	output: no
*/
void Communicator::startHandleRequests()
{
	bindAndListen();

	while (true)
	{
		Communicator::handleNewClient(Communicator::accept());
	}
}

/*
	usage: the method removes a client from the server
	in: the client socket
	out: no
*/
void Communicator::removeClient(SOCKET clientSocket)
{
	this->m_clients.erase(clientSocket);
}

/*
	usage: the operator gets the request handler of socket
	in: the socket
	out: the request handler
*/
IRequestHandler*& Communicator::operator[](const SOCKET& socket)
{
	return this->m_clients[socket];
}

/*
	usage: the method binds and start listening for new clients
	input: no
	output: no
*/
void Communicator::bindAndListen() const
{
	struct sockaddr_in socketAddress = { 0 };
	socketAddress.sin_port = htons(PORT);
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = INTERFACE;

	if (::bind(this->_listeningSocket, (struct sockaddr*) & socketAddress, sizeof(socketAddress)) == SOCKET_ERROR)
	{
		throw exception(__FUNCTION__ " - bind");
	}

	if (::listen(this->_listeningSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw exception(__FUNCTION__ " - listen");
	}
}

/*
	usage: the method handles a new client
	input: the client socket.
	output: none.
*/
void Communicator::handleNewClient(SOCKET clientSocket) 
{
	this->m_clients[clientSocket] = RequestHandlerFactory::getInstance().createLoginRequestHandler();

	thread clientThread(clientThread, clientSocket);
	clientThread.detach();
}

/*
	usage: the method accepts a new client
	input: no
	output: the client socket
*/
SOCKET Communicator::accept() const
{
	SOCKET clientSocket = ::accept(this->_listeningSocket, NULL, NULL);

	if (clientSocket == INVALID_SOCKET)
	{
		throw exception(__FUNCTION__);
	}

	return clientSocket;
}
