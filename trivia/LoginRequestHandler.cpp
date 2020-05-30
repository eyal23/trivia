#include <vector>

#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Constants.h"

using std::vector;

/*
	usage: constructor
	in: reference to the requestHandlerFactory
	out: no
*/
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) :
	m_handlerFacotry(handlerFactory), m_loginManager(handlerFactory.getLoginManager())
{
}

/*
	usage: the methods checks if a request is relevant
	in: the request info
	out: if the request is relevant
*/
bool LoginRequestHandler::isRequestRelevant(const RequestInfo requestInfo) const
{
	return requestInfo.id == LOGIN_REQUEST || requestInfo.id == SIGN_UP_REQUEST;
}

/*
	usage: the methods handles a request
	in: the request info
	out: the RequestResult object
*/
RequestResult LoginRequestHandler::handleRequest(const RequestInfo requestInfo)
{
	if (requestInfo.id == LOGIN_REQUEST)
	{
		return this->login(requestInfo);
	}
	else
	{
		return this->signup(requestInfo);
	}
}

/*
	usage: the method tries to login into user's account, returns correspondly
	in: the request info
	out: if the login was succesful
*/
RequestResult LoginRequestHandler::login(const RequestInfo requestInfo) const
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

/*
	usage: the method tries to sign up a user, returns correspondly
	in: the request info
	out: if the sign up was succesful
*/
RequestResult LoginRequestHandler::signup(const RequestInfo requestInfo) const
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
