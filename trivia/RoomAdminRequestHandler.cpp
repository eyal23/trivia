#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Constants.h"


/*
    usage: constructor
    in: the handler factory, the room id, the logged user
    out: no
*/
RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, int roomId, LoggedUser loggedUser) :
    RoomRequestHandler(roomId, loggedUser, handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}

/*
    usage: the method checks if a request is relevant
    in: the request info
    out: if the request is relevant
*/
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return requestInfo.id == START_GAME_REQUEST ||
        requestInfo.id == CLOSE_ROOM_REQUEST ||
        requestInfo.id == GET_ROOM_STATE_REQUEST;
}

/*
	usage: the method handles a request
	in: the request info
	out: the request result
*/
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	if (!this->isRequestRelevant(requestInfo))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "ERROR" })),
			nullptr
		};
	}

	try
	{
		switch (requestInfo.id)
		{
		case CLOSE_ROOM_REQUEST:
			return this->closeRoom();
			break;

		case START_GAME_REQUEST:
			return this->startGame();
			break;

		case GET_ROOM_STATE_REQUEST:
			return this->getRoomState();
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
    usage: the method closes a room
    in: no
    out: the request result
*/
RequestResult RoomAdminRequestHandler::closeRoom()
{
    this->m_roomManager.closeRoom(this->m_roomId);
    this->m_roomManager.tryDeleteRoom(this->m_roomId, this->m_user);
    
    return {
        JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse({ 1 })),
        this->m_handlerFactory.createMenuRequestHandler(this->m_user)
    };
}
