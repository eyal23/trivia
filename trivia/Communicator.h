#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <map>

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

#pragma comment(lib, "ws2_32.lib")

using std::map;

class Communicator
{
private:
	map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	SOCKET _listeningSocket;

public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();

	void startHandleRequests();
	RequestHandlerFactory& getHandlerFactory();
	void removeClient(SOCKET clientSocket);
	IRequestHandler*& operator[](const SOCKET& socket);

private:
	void bindAndListen() const;
	void handleNewClient(SOCKET clientSocket);
    SOCKET accept() const;
};