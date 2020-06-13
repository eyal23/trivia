#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"

class RequestHandlerFactory;


class RoomRequestHandler: public IRequestHandler
{
protected:
	int m_roomId;
	LoggedUser m_user;
	RoomManager& m_roomManager;

public:
	RoomRequestHandler(int roomId, LoggedUser loggedUser, RoomManager& roomManager);

	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
	virtual bool isRequestRelevant(RequestInfo requestInfo) const = 0;

protected:
	RequestResult getRoomState();
	RequestResult startGame();
};

