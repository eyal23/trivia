#include "RoomRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

RoomRequestHandler::RoomRequestHandler(int roomId, LoggedUser loggedUser, RoomManager& roomManager) :
    m_roomId(roomId), m_user(loggedUser), m_roomManager(roomManager)
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

	if (!this->m_roomManager.doesRoomExist(this->m_roomId))
	{
		return this->leaveRoom();
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

RequestResult RoomRequestHandler::getRoomState()
{
    RoomState roomState = this->m_roomManager.getRoomState(this->m_roomId);

    return {
        JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse({ 1, roomState.hasGameBegun, roomState.players, roomState.questionsCount, roomState.answerTimeout })),
        nullptr
    };
}
