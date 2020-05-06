#pragma once
#include <iostream>
#include "Communicator.h"


class Server
{
public:
	void run();

private:
	Communicator m_Communicator;
};

