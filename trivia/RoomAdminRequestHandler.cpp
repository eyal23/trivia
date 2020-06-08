#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser) :
    RoomRequestHandler(handlerFactory, room, loggedUser)
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
