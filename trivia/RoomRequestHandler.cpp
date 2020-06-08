#include "RoomRequestHandler.h"

RoomRequestHandler::RoomRequestHandler(Room room, LoggedUser loggedUser) :
    m_room(room), m_user(loggedUser)
{
}

RequestResult RoomRequestHandler::handleRequest(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult RoomRequestHandler::getRoomState(RequestInfo requestInfo)
{
    return RequestResult();
}
