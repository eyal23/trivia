#pragma once

#include "RoomRequestHandler.h"

class RoomAdminRequestHandler: public RoomRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser);

	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult closeRoom(RequestInfo requestInfo);
	RequestInfo startGame(RequestInfo requestInfo);
};

