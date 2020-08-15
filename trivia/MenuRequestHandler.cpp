#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"


/*
	usage: constructor
	in: the handler factory, the logged user
	out: no
*/
MenuRequestHandler::MenuRequestHandler(LoggedUser loggedUser) :
	m_user(loggedUser)
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
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "Request is non-relevant" })),
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
	in: no
	out: the request result
*/
RequestResult MenuRequestHandler::signout()
{
	if (LoginManager::getInstance().logout(this->m_user.getUsername()))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(LogoutResponse({ 1 })),
			RequestHandlerFactory::getInstance().createLoginRequestHandler()
		};
	}

	return {
		JsonResponsePacketSerializer::serializeResponse(LogoutResponse({ 0 })),
		this
	};
}

/*
	usage: the method gets all the rooms
	in: no
	out: the request result
*/
RequestResult MenuRequestHandler::getRooms()
{
	return {
		JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse({ 1, RoomManager::getInstance().getRooms() })),
		this
	};
}

/*
	usage: the method gets all the players in a room
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo)
{
	GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);

	return {
		JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse({ 1, RoomManager::getInstance().getPlayersInRoom(getPlayersInRoomRequest.roomId) })),
		this
	};
}

/*
	usage: the method gets the statistics about a user
	in: no
	out: the request result
*/
RequestResult MenuRequestHandler::getStatistics()
{
	return {
		JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse({ 1, StatisticsManager::getInstance().getStatistics(this->m_user) })),
		this
	};
}

/*
	usage: the method joins a user into a room
	in: the request info
	out: the request result
*/
RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo)
{
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);

	if (RoomManager::getInstance().joinRoom(joinRoomRequest.roomId, this->m_user))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse({ 1 })),
			RequestHandlerFactory::getInstance().createRoomMemberRequestHandler(this->m_user, joinRoomRequest.roomId)
		};
	}

	return {
			JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse({ 0 })),
			this
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

	int id = RoomManager::getInstance().createRoom(
		this->m_user, 
		{ 
			0, 
			createRoomRequest.roomName, 
			createRoomRequest.maxUsers, 
			createRoomRequest.answerTimout, 
			createRoomRequest.questionCount, 
			false,
			true
		}
	);

	return {
		JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse({ 1 })),
		RequestHandlerFactory::getInstance().createRoomAdminRequestHandler(this->m_user, id)
	};
}
