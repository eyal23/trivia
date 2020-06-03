#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser loggedUser) :
	m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_statisticsManager(handlerFactory.getStatisticsManager()), m_user(loggedUser)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo requestInfo) const
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo requestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo) const
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo) const
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo) const
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getStatistics(RequestInfo requestInfo) const
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo) const
{
	return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo) const
{
	return RequestResult();
}
