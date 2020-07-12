#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class RequestHandlerFactory;

class GameRequestHandler: public IRequestHandler
{
private:
	unsigned int m_gameId;
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;

public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, unsigned int gameId, LoggedUser user);

	bool isRequestRelevant(RequestInfo requestInfo) const override;
	RequestResult handleRequest(RequestInfo requestInfo) override;

private:
	RequestResult getQuestion();
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults();
	RequestResult leaveGame();
};

