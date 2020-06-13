#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Constants.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, int roomId, LoggedUser loggedUser) :
    RoomRequestHandler(roomId, loggedUser, handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return requestInfo.id == START_GAME_REQUEST ||
        requestInfo.id == CLOSE_ROOM_REQUEST ||
        requestInfo.id == GET_ROOM_STATE_REQUEST;
}

RequestResult RoomAdminRequestHandler::closeRoom()
{
    this->m_roomManager.closeRoom(this->m_roomId);
    this->m_roomManager.tryDeleteRoom(this->m_roomId, this->m_user);
    
    return {
        JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse({ 1 })),
        this->m_handlerFactory.createMenuRequestHandler(this->m_user)
    };
}

RequestResult RoomAdminRequestHandler::startGame()
{
    this->m_roomManager[this->m_roomId].activateRoom();

    return {
        JsonResponsePacketSerializer::serializeResponse(StartGameResponse({ 1 })),
        nullptr
    };
}
