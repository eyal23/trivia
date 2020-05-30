#pragma once

#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;

public:
	LoginRequestHandler* createLoginRequestHandler() const;
	LoginManager& getLoginManager() const;
};

