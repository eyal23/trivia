#include <vector>

#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Constants.h"

using std::vector;


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) :
	m_handlerFacotry(handlerFactory), m_loginManager(handlerFactory.getLoginManager())
{
}

/*
	usage: the methods checks if a request is relevant
	in: the request info
	out: if the request is relevant
*/
bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	return requestInfo.id == LOGIN_REQUEST || requestInfo.id == SIGN_UP_REQUEST;
}

/*
	usage: the methods handles a request
	in: the request info
	out: the RequestResult object
*/
RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
	if (requestInfo.id == LOGIN_REQUEST)
	{
		return this->login(requestInfo);
	}
	else
	{
		return this->signUp(requestInfo);
	}
}

RequestResult LoginRequestHandler::login(RequestInfo requestInfo)
{
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	
	if (this->m_loginManager.login(loginRequest.username, loginRequest.password))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 1 })),
			new MenuRequestHandler()
		};
	}
	
	return {
		JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "ERROR" })),
		this->m_handlerFacotry.createLoginRequestHandler()
	};
}

RequestResult LoginRequestHandler::signUp(RequestInfo requestInfo)
{
	SignUpRequest signUpRequest = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestInfo.buffer);

	if (this->m_loginManager.signup(signUpRequest.username, signUpRequest.password, signUpRequest.email))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 1 })),
			new MenuRequestHandler()
		};
	}

	return {
		JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "ERROR" })),
		this->m_handlerFacotry.createLoginRequestHandler()
	};
}
