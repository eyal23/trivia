#pragma once

#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"

class RequestHandlerFactory;


class RoomRequestHandler: public IRequestHandler
{
protected:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;

public:
	RoomRequestHandler(Room room, LoggedUser loggedUser, RoomManager& roomManager);

	RequestResult handleRequest(RequestInfo requestInfo) override;
	virtual bool isRequestRelevant(RequestInfo requestInfo) const = 0;

protected:
	RequestResult getRoomState(RequestInfo requestInfo);
	virtual RequestResult leaveRoom(RequestInfo requestInfo) = 0;
	virtual RequestResult closeRoom(RequestInfo requestInfo) = 0;
	virtual RequestResult startGame(RequestInfo requestInfo) = 0;
};

