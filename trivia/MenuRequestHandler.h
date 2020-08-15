#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"


class MenuRequestHandler: public IRequestHandler
{
private:
	LoggedUser m_user;

public:
	MenuRequestHandler(LoggedUser loggedUser);

	bool isRequestRelevant(const RequestInfo requestInfo) const override;
	RequestResult handleRequest(const RequestInfo requestInfo) override;

private:
	RequestResult signout();
	RequestResult getRooms();
	RequestResult getPlayersInRoom(RequestInfo requestInfo);
	RequestResult getStatistics();
	RequestResult joinRoom(RequestInfo requestInfo);
	RequestResult createRoom(RequestInfo requestInfo) const;
};

