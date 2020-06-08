#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser) :
    RoomRequestHandler(room, loggedUser), m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager())
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
