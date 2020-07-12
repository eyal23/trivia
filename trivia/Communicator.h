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
	SOCKET _listeningSocket;

public:
	static Communicator& getInstance()
	{
		static Communicator instance;
		return instance;
	}

	void startHandleRequests();
	void removeClient(SOCKET clientSocket);
	IRequestHandler*& operator[](const SOCKET& socket);

	Communicator(Communicator const&) = delete;
	void operator=(Communicator const&) = delete;

private:
	Communicator();
	~Communicator();

	void bindAndListen() const;
	void handleNewClient(SOCKET clientSocket);
    SOCKET accept() const;
};