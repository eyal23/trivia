#pragma once

#include "RoomRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler: public RoomRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;

public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser);

	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult closeRoom(RequestInfo requestInfo) override;
	RequestResult startGame(RequestInfo requestInfo) override;
};

