#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser) :
    RoomRequestHandler(handlerFactory, room, loggedUser)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return false;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{
    return RequestResult();
}
