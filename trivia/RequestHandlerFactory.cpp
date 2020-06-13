#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "IDatabase.h"


/*
	usage: constructor
	in: the database
	out:no
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase& database) :
	m_loginManager(LoginManager(database)), m_statisticsManager(StatisticsManager(database))
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

/*
	usage: the method creates a menu request handler
	in: no
	out: the menu request handler
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser loggedUser)
{
	return new MenuRequestHandler(*this, loggedUser);
}

/*
	usage: the method creates a room admin request handler
	in: no
	out: the room admin request handler
*/
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser loggedUser, int roomId)
{
	return new RoomAdminRequestHandler(*this, roomId, loggedUser);
}

/*
	usage: the method creates a room member request handler
	in: no
	out: the room member request handler
*/
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser loggedUser, int roomId)
{
	return new RoomMemberRequestHandler(*this, roomId, loggedUser);
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

/*
	usage: the method gets the room manager
	in: no
	out: the room manager
*/
RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

/*
	usage: the method gets the statistics manager
	in: no
	out: the statistics manager
*/
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}
