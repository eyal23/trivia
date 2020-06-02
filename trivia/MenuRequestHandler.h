#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler: public IRequestHandler
{
private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;

public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo requestInfo) const override;
	RequestResult handleRequest(const RequestInfo requestInfo) override;

private:
	RequestResult signout(RequestInfo requestInfo) const;
	RequestResult getRooms(RequestInfo requestInfo) const;
	RequestResult getPlayersInRoom(RequestInfo requestInfo) const;
	RequestResult getStatistics(RequestInfo requestInfo) const;
	RequestResult joinRoom(RequestInfo requestInfo) const;
	RequestResult createRoom(RequestInfo requestInfo) const;
};

