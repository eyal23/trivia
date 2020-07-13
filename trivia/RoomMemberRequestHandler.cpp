#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "sqliteDataBase.h"


/*
    usage: constructor
    in: the handler factory, the room id, the logged user
    out: no
*/
RoomMemberRequestHandler::RoomMemberRequestHandler(int roomId, LoggedUser loggedUser) :
	m_roomId(roomId), m_user(loggedUser)
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
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "Request is non-relevant" })),
			nullptr
		};
	}

	try
	{
		switch (requestInfo.id)
		{
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
	RoomManager::getInstance().tryDeleteRoom(this->m_roomId, this->m_user);

    return {
        JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse({ 1 })),
        RequestHandlerFactory::getInstance().createMenuRequestHandler(this->m_user)
    };
}

/*
	usage: the method gets a room's state
	in: no
	out: the request result
*/
RequestResult RoomMemberRequestHandler::getRoomState()
{
	RoomState roomState = RoomManager::getInstance().getRoomState(this->m_roomId);

	if (!roomState.isRoomOpen)
	{
		RoomManager::getInstance().tryDeleteRoom(this->m_roomId, this->m_user);
	}

	vector<LoggedUser> roomUsers;
	vector<string> stringUsers = RoomManager::getInstance()[this->m_roomId].getAllUsers();

	for (int i = 0; i < stringUsers.size(); i++)
	{
		roomUsers.push_back(LoggedUser(stringUsers[i]));
	}

	if (roomState.hasGameBegun)
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse({ 1, roomState.hasGameBegun, roomState.isRoomOpen, roomState.players, roomState.questionsCount, roomState.answerTimeout })),
			RequestHandlerFactory::getInstance().createGameRequestHandler(Game(roomUsers, SqliteDatabase::getInstance().getQuestions()), this->m_user)
		};
	}
	else
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse({ 1, roomState.hasGameBegun, roomState.isRoomOpen, roomState.players, roomState.questionsCount, roomState.answerTimeout })),
			this
		};
	}
}