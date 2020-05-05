#pragma once
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <map>
#include <WinSock2.h>
#include "iRequestHandler.h"

using std::map;

class Communicator
{
public:
	void startHandleRequests();


private:
	void bindAndListen();
	void handleNewClient();

	map<SOCKET, iRequestHandler*> m_clients;
};

