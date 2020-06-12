#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, int roomId, LoggedUser loggedUser) :
    RoomRequestHandler(roomId, loggedUser, handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return requestInfo.id == LEAVE_ROOM_REQUEST ||
        requestInfo.id == GET_ROOM_STATE_REQUEST;
}

RequestResult RoomMemberRequestHandler::leaveRoom()
{
    if (this->m_roomManager.doesRoomExist(this->m_roomId))
    {
        this->m_roomManager[this->m_roomId].removeUser(this->m_user);
    }

    return {
        JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse({ 1 })),
        this->m_handlerFactory.createMenuRequestHandler(this->m_user)
    };
}
