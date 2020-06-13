#include "RoomRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"


/*
	usage: constructor
	in: the room id, the logged user, the room manager
	out: no
*/
RoomRequestHandler::RoomRequestHandler(int roomId, LoggedUser loggedUser, RoomManager& roomManager) :
    m_roomId(roomId), m_user(loggedUser), m_roomManager(roomManager)
{
}

/*
	usage: the method gets a room's state
	in: no
	out: the request result
*/
RequestResult RoomRequestHandler::getRoomState()
{
    RoomState roomState = this->m_roomManager.getRoomState(this->m_roomId);

    return {
        JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse({ 1, roomState.hasGameBegun, roomState.players, roomState.questionsCount, roomState.answerTimeout })),
        nullptr
    };
}

/*
	usage: the method starts a game
	in: no
	out: the request result
*/
RequestResult RoomRequestHandler::startGame()
{
	this->m_roomManager[this->m_roomId].activateRoom();

	return {
		JsonResponsePacketSerializer::serializeResponse(StartGameResponse({ 1 })),
		nullptr
	};
}
