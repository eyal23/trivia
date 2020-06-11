#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Constants.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser) :
    RoomRequestHandler(room, loggedUser, handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return requestInfo.id == START_GAME_REQUEST ||
        requestInfo.id == CLOSE_ROOM_REQUEST ||
        requestInfo.id == GET_ROOM_STATE_REQUEST;

}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo)
{
    this->m_roomManager.deleteRoom(this->m_room.getMetadata().id);
    
    return {
        JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse({ 1 })),
        this->m_handlerFactory.createMenuRequestHandler(this->m_user)
    };
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo)
{
    this->m_room.activateRoom();

    return {
        JsonResponsePacketSerializer::serializeResponse(StartGameResponse({ 1 })),
        nullptr
    };
}
