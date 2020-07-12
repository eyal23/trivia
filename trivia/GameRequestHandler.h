#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"


class GameRequestHandler: public IRequestHandler
{
private:
	unsigned int m_gameId;
	LoggedUser m_user;

public:
	GameRequestHandler(unsigned int gameId, LoggedUser user);

	bool isRequestRelevant(RequestInfo requestInfo) const override;
	RequestResult handleRequest(RequestInfo requestInfo) override;

private:
	RequestResult getQuestion();
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults();
	RequestResult leaveGame();
};

