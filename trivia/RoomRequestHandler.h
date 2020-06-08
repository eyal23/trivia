#pragma once

#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"

class RequestHandlerFactory;


class RoomRequestHandler: public IRequestHandler
{
protected:
	Room m_room;
	LoggedUser m_user;

public:
	RoomRequestHandler(Room room, LoggedUser loggedUser);

	RequestResult handleRequest(RequestInfo requestInfo) override;

protected:
	RequestResult getRoomState(RequestInfo requestInfo);
};

