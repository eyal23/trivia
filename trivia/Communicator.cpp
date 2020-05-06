#include "Communicator.h"
#include "WSAInitializer.h"
#include "LoginRequestHandler.h"

#include <iostream>
#include <exception>
#include <thread>

static const unsigned short PORT = 8826;
static const unsigned int INTERFACE = 0;

void clientThread(Communicator& communicator)
{
	
}

Communicator::Communicator()
{
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_socket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Communicator::~Communicator()
{
	try
	{
		::closesocket(_socket);
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

	if (::bind(_socket, (struct sockaddr*) & socketAddress, sizeof(socketAddress)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	this->m_clients[clientSocket] = new LoginRequestHandler;

	std::thread clientThread(clientThread, std::ref(*this));
	clientThread.detach();
}

SOCKET Communicator::accept()
{
	SOCKET clientSocket = ::accept(_socket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__);
	}

	return clientSocket;
}
