#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "Game.h"

class RequestHandlerFactory;

class GameRequestHandler: public IRequestHandler
{
private:
	Game m_game;
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;

public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, Game game, LoggedUser user);

	bool isRequestRelevant(RequestInfo requestInfo) const override;
	RequestResult handleRequest(RequestInfo requestInfo) override;

private:
	RequestResult getQuestion(RequestInfo requestInfo);
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults(RequestInfo requestInfo);
	RequestResult leaveGame(RequestInfo requestInfo);
};

