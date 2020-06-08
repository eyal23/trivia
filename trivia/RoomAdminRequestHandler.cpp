#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser) :
    RoomRequestHandler(room, loggedUser), m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager())
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return false;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestInfo RoomAdminRequestHandler::startGame(RequestInfo requestInfo)
{
    return RequestInfo();
}
