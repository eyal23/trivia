#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler: public IRequestHandler
{
private:
	int m_roomId;
	LoggedUser m_user;

public:
	RoomMemberRequestHandler(int roomId, LoggedUser loggedUser);

	RequestResult handleRequest(RequestInfo requestInfo) override;
	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult leaveRoom();
	RequestResult getRoomState();
};

