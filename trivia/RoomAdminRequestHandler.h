#pragma once

#include "RoomRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler: public RoomRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	RoomManager& m_roomManager;

public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser);

	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult closeRoom(RequestInfo requestInfo);
	RequestInfo startGame(RequestInfo requestInfo);
};

