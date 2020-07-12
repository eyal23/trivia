#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler: public IRequestHandler
{
private:
	int m_roomId;
	LoggedUser m_user;

public:
	RoomAdminRequestHandler(int roomId, LoggedUser loggedUser);

	RequestResult handleRequest(RequestInfo requestInfo) override;
	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult closeRoom();
	RequestResult getRoomState();
	RequestResult startGame();
};

