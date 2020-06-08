#pragma once

#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "LoggedUser.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	IDatabase* m_database;

public:
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser loggedUser);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser loggedUser, Room room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser loggedUser, Room room);
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
};

