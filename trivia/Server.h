#pragma once

#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server
{
private:
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;

public:
	Server(IDatabase& database);

	void run();
};

