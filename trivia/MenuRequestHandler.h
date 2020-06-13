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
	RequestResult getRooms() const;
	RequestResult getPlayersInRoom(RequestInfo requestInfo) const;
	RequestResult getStatistics() const;
	RequestResult joinRoom(RequestInfo requestInfo) const;
	RequestResult createRoom(RequestInfo requestInfo) const;
};

