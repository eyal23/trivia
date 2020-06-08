#include "RoomRequestHandler.h"

RoomRequestHandler::RoomRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser) :
    m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_room(room), m_user(loggedUser)
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
