#pragma once

#include "RoomRequestHandler.h"

class RoomMemberRequestHandler: public RoomRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser);

	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult leaveRoom(RequestInfo requestInfo);
};

