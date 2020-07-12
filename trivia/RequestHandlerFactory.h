#pragma once

#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
#include "LoggedUser.h"
#include "Game.h"


class RequestHandlerFactory
{
public:
	static RequestHandlerFactory& getInstance()
	{
		static RequestHandlerFactory instance;
		return instance;
	}

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser loggedUser);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser loggedUser, int roomId);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser loggedUser, int roomId);
	GameRequestHandler* createGameRequestHandler(Game game, LoggedUser loggedUser);

	RequestHandlerFactory(RequestHandlerFactory const&) = delete;
	void operator=(RequestHandlerFactory const&) = delete;

private:
	RequestHandlerFactory() {}
};

