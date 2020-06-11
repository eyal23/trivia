#include "RoomRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

RoomRequestHandler::RoomRequestHandler(Room room, LoggedUser loggedUser, RoomManager& roomManager) :
    m_room(room), m_user(loggedUser), m_roomManager(roomManager)
{
}

RequestResult RoomRequestHandler::handleRequest(RequestInfo requestInfo)
{
	if (!this->isRequestRelevant(requestInfo))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "ERROR" })),
			nullptr
		};
	}

	if (!this->m_roomManager.doesRoomExist(this->m_room.getMetadata().id))
	{
		return this->leaveRoom(requestInfo);
	}

	try
	{
		switch (requestInfo.id)
		{
		case CLOSE_ROOM_REQUEST:
			return this->closeRoom(requestInfo);
			break;

		case START_GAME_REQUEST:
			return this->startGame(requestInfo);
			break;

		case GET_ROOM_STATE_REQUEST:
			return this->getRoomState(requestInfo);
			break;

		case LEAVE_ROOM_REQUEST:
			return this->leaveRoom(requestInfo);
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

RequestResult RoomRequestHandler::getRoomState(RequestInfo requestInfo)
{
    RoomData metadata = this->m_room.getMetadata();

    return {
        JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse({ 1, metadata.isActive, this->m_room.getAllUsers(), metadata.questionsCount, metadata.timePerQuestion })),
        nullptr
    };
}
