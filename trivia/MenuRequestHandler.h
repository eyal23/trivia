#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler: public IRequestHandler
{
private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;

public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser loggedUser);

	bool isRequestRelevant(const RequestInfo requestInfo) const override;
	RequestResult handleRequest(const RequestInfo requestInfo) override;

private:
	RequestResult signout() const;
	RequestResult getRooms();
	RequestResult getPlayersInRoom(RequestInfo requestInfo);
	RequestResult getStatistics();
	RequestResult joinRoom(RequestInfo requestInfo);
	RequestResult createRoom(RequestInfo requestInfo) const;
};

