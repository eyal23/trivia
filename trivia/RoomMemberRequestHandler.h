#pragma once

#include "RoomRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler: public RoomRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	RoomManager& m_roomManager;

public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser);

	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult leaveRoom(RequestInfo requestInfo);
};

