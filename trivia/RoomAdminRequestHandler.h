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

	bool isRequestRelevant(RequestInfo requestInfo) const override;

private:
	RequestResult closeRoom() override;
	RequestResult startGame() override;
};

