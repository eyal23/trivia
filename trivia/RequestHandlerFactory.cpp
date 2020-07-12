#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"


/*
	usage: the method creates a login request handler
	in: no
	out: the login request handler
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler();
}

/*
	usage: the method creates a menu request handler
	in: no
	out: the menu request handler
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser loggedUser)
{
	return new MenuRequestHandler(loggedUser);
}

/*
	usage: the method creates a room admin request handler
	in: no
	out: the room admin request handler
*/
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser loggedUser, int roomId)
{
	return new RoomAdminRequestHandler(roomId, loggedUser);
}

/*
	usage: the method creates a room member request handler
	in: no
	out: the room member request handler
*/
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser loggedUser, int roomId)
{
	return new RoomMemberRequestHandler(roomId, loggedUser);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(Game game, LoggedUser loggedUser)
{
	return nullptr;
}
