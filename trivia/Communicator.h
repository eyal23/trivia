#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include "IRequestHandler.h"

#pragma comment(lib, "ws2_32.lib")

using std::map;

class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequests();

private:
	void bindAndListen() const;
	void handleNewClient(SOCKET clientSocket);
    SOCKET accept() const;

private:
	map<SOCKET, IRequestHandler*> m_clients;
	SOCKET _listeningSocket;

};