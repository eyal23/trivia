#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, Game game, LoggedUser user) :
    m_handlerFactory(handlerFactory), m_game(game), m_user(user)
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return false;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
    return RequestResult();
}
