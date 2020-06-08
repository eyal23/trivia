#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "Room.h"
#include "LoggedUser.h"

class RoomRequestHandler: public IRequestHandler
{
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

public:
	RoomRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser);

	RequestResult handleRequest(RequestInfo requestInfo) override;

protected:
	RequestResult getRoomState(RequestInfo requestInfo);
};

