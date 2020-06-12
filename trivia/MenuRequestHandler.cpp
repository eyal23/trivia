#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"


/*
	usage: constructor
	in: the handler factory, the logged user
	out: no
*/
MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser loggedUser) :
	m_handlerFactory(handlerFactory), m_user(loggedUser)
{
}

/*
	usage: the method checks if a request is relevant
	in: the request info
	out: if the request is relevant
*/
bool MenuRequestHandler::isRequestRelevant(const RequestInfo requestInfo) const
{
	return requestInfo.id == LOGOUT_REQUEST ||
		requestInfo.id == CREATE_ROOM_REQUEST ||
		requestInfo.id == GET_ROOMS_REQUEST ||
		requestInfo.id == GET_PLAYERS_IN_ROOM_REQUEST ||
		requestInfo.id == JOIN_ROOM_REQUEST ||
		requestInfo.id == GET_STATISTICS_REQUEST;
}

/*
	usage: the method handles a request
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::handleRequest(const RequestInfo requestInfo)
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
		case LOGOUT_REQUEST:
			return this->signout();
			break;

		case CREATE_ROOM_REQUEST:
			return this->createRoom(requestInfo);
			break;

		case GET_ROOMS_REQUEST:
			return this->getRooms();
			break;

		case GET_PLAYERS_IN_ROOM_REQUEST:
			return this->getPlayersInRoom(requestInfo);
			break;

		case JOIN_ROOM_REQUEST:
			return this->joinRoom(requestInfo);
			break;

		case GET_STATISTICS_REQUEST:
			return this->getStatistics();
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
	usage: the method signs out a user
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::signout() const
{
	if (this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername()))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(LogoutResponse({ 1 })),
			nullptr
		};
	}

	return {
		JsonResponsePacketSerializer::serializeResponse(LogoutResponse({ 0 })),
		nullptr
	};
}

/*
	usage: the method gets all the rooms
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::getRooms() const
{
	return {
		JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse({ 1, this->m_handlerFactory.getRoomManager().getRooms() })),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	};
}

/*
	usage: the method gets all the players in a room
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo) const
{
	GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);

	return {
		JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse({ this->m_handlerFactory.getRoomManager().getPlayersInRoom(getPlayersInRoomRequest.roomId) })),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	};
}

/*
	usage: the method gets the statistics about a user
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::getStatistics() const
{
	return {
		JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse({ 1, this->m_handlerFactory.getStatisticsManager().getStatistics(this->m_user) })),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	};
}

/*
	usage: the method joins a user into a room
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo) const
{
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);

	if (this->m_handlerFactory.getRoomManager().joinRoom(joinRoomRequest.roomId, this->m_user))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse({ 1 })),
			this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, joinRoomRequest.roomId)
		};
	}

	return {
			JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse({ 0 })),
			this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	};
}

/*
	usage: the method creates a room
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo) const
{
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);

	int id = this->m_handlerFactory.getRoomManager().createRoom(
		this->m_user, 
		{ 
			0, 
			createRoomRequest.roomName, 
			createRoomRequest.maxUsers, 
			createRoomRequest.answerTimout, 
			createRoomRequest.questionCount, 
			false 
		}
	);

	return {
		JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse({ 1 })),
		this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, id)
	};
}
