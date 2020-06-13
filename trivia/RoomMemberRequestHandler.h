#pragma once

#include "RoomRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler: public RoomRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;

public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, int roomId, LoggedUser loggedUser);

	RequestResult handleRequest(RequestInfo requestInfo) override;
	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult leaveRoom();
};

