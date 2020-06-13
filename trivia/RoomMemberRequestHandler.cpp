#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"


/*
    usage: constructor
    in: the handler factory, the room id, the logged user
    out: no
*/
RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, int roomId, LoggedUser loggedUser) :
    RoomRequestHandler(roomId, loggedUser, handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}

/*
    usage: the method checks if a request is relevant
    in: the request info
    out: if the request is relevant
*/
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return requestInfo.id == LEAVE_ROOM_REQUEST ||
		requestInfo.id == START_GAME_REQUEST ||
        requestInfo.id == GET_ROOM_STATE_REQUEST;
}

/*
	usage: the method handles a request
	in: the request info
	out: the request result
*/
RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo)
{
	if (!this->isRequestRelevant(requestInfo))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "ERROR" })),
			nullptr
		};
	}

	if (!this->m_roomManager.isRoomOpen(this->m_roomId))
	{
		return this->leaveRoom();
	}

	try
	{
		switch (requestInfo.id)
		{
		case START_GAME_REQUEST:
			return this->startGame();
			break;

		case GET_ROOM_STATE_REQUEST:
			return this->getRoomState();
			break;

		case LEAVE_ROOM_REQUEST:
			return this->leaveRoom();
			break;
		}
	}

	catch (const std::exception& e)
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "ERROR" })),
			nullptr
		};
	}
}

/*
    usage: the method leaves a room
    in: no
    out: the request result
*/
RequestResult RoomMemberRequestHandler::leaveRoom()
{
    this->m_roomManager.tryDeleteRoom(this->m_roomId, this->m_user);

    return {
        JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse({ 1 })),
        this->m_handlerFactory.createMenuRequestHandler(this->m_user)
    };
}
