#include "Communicator.h"
#include "WSAInitializer.h"
#include "LoginRequestHandler.h"

#include <iostream>
#include <exception>
#include <thread>

#define BYTES_AMOUNT 5

using std::exception;
using std::cout;
using std::string;
using std::endl;
using std::thread;
using std::ref;

static const unsigned short PORT = 8826;
static const unsigned int INTERFACE = 0;

void clientThread(Communicator& communicator, SOCKET& clientSocket)
{
	if (send(clientSocket, "Hello", BYTES_AMOUNT, 0) == INVALID_SOCKET)
	{
		throw exception("Error while sending message to client");
	}

	char* data = new char[BYTES_AMOUNT];

	if (recv(clientSocket, data, BYTES_AMOUNT, 0) == INVALID_SOCKET)
	{
		throw exception("Error while reciving message from client");
	}

	cout << string(data) << endl;
	system("pause");
}

Communicator::Communicator()
{
	this->_listeningSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->_listeningSocket == INVALID_SOCKET)
	{
		throw exception(__FUNCTION__ " - socket");
	}
}

Communicator::~Communicator()
{
	try
	{
		::closesocket(this->_listeningSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();

	while (true)
	{
		Communicator::handleNewClient(Communicator::accept());
	}                           
}

void Communicator::bindAndListen()
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

void Communicator::handleNewClient(SOCKET clientSocket)
{
	this->m_clients[clientSocket] = new LoginRequestHandler;

	thread clientThread(clientThread, ref(*this), ref(clientSocket));
	clientThread.detach();
}

SOCKET Communicator::accept()
{
	SOCKET clientSocket = ::accept(this->_listeningSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
	{
		throw exception(__FUNCTION__);
	}

	return clientSocket;
}
