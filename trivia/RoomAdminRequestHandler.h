#pragma once

#include "RoomRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler: public RoomRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;

public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, int roomId, LoggedUser loggedUser);

	RequestResult handleRequest(RequestInfo requestInfo) override;
	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult closeRoom();
};

