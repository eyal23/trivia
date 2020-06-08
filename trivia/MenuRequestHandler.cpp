#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser loggedUser) :
	m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_statisticsManager(handlerFactory.getStatisticsManager()), m_user(loggedUser)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo requestInfo) const
{
	return requestInfo.id == LOGOUT_REQUEST ||
		requestInfo.id == CREATE_ROOM_REQUEST ||
		requestInfo.id == GET_ROOMS_REQUEST ||
		requestInfo.id == GET_PLAYERS_IN_ROOM_REQUEST ||
		requestInfo.id == JOIN_ROOM_REQUEST ||
		requestInfo.id == GET_STATISTICS_REQUEST;
}

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
			return this->signout(requestInfo);
			break;

		case CREATE_ROOM_REQUEST:
			return this->createRoom(requestInfo);
			break;

		case GET_ROOMS_REQUEST:
			return this->getRooms(requestInfo);
			break;

		case GET_PLAYERS_IN_ROOM_REQUEST:
			return this->getPlayersInRoom(requestInfo);
			break;

		case JOIN_ROOM_REQUEST:
			return this->joinRoom(requestInfo);
			break;

		case GET_STATISTICS_REQUEST:
			return this->getStatistics(requestInfo);
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

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo) const
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

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo) const
{
	return {
		JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse({ 1, this->m_roomManager.getRooms() })),
		nullptr
	};
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo) const
{
	GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);

	return {
		JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse({ this->m_roomManager.getPlayersInRoom(getPlayersInRoomRequest.roomId) })),
		nullptr
	};
}

RequestResult MenuRequestHandler::getStatistics(RequestInfo requestInfo) const
{
	return { 
		JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse({ 1, this->m_statisticsManager.getStatistics(this->m_user) })),
		nullptr
	};
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo) const
{
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);

	if (this->m_roomManager.joinRoom(joinRoomRequest.roomId, this->m_user))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse({ 1 })),
			nullptr
		};
	}

	return {
			JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse({ 0 })),
			nullptr
	};
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo) const
{
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);

	this->m_roomManager.createRoom(
		this->m_user, 
		{ 
			0, 
			createRoomRequest.roomName, 
			createRoomRequest.maxUsers, 
			createRoomRequest.answerTimout, 
			createRoomRequest.questionCount, 
			0 
		}
	);

	return {
		JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse({ 1 })),
		nullptr
	};
}
