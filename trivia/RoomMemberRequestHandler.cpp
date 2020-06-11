#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser loggedUser) :
    RoomRequestHandler(room, loggedUser, handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return requestInfo.id == LEAVE_ROOM_REQUEST ||
        requestInfo.id == GET_ROOM_STATE_REQUEST;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{
    if (this->m_roomManager.doesRoomExist(this->m_room.getMetadata().id))
    {
        this->m_roomManager[this->m_room.getMetadata().id].removeUser(this->m_user);
    }

    return {
        JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse({ 1 })),
        this->m_handlerFactory.createMenuRequestHandler(this->m_user)
    };
}
