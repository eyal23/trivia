#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"


/*
	usage: constructor
	in: the database
	out:no
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
	m_database(database), m_loginManager(LoginManager(database))
{
}

/*
	usage: the method creates a login request handler
	in: no
	out: the login request handler
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	return nullptr;
}

/*
	usage: the method gets the login manager
	in: no
	out: the login manager
*/
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	// TODO: insert return statement here
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	// TODO: insert return statement here
}
