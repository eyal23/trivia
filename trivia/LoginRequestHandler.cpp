#include <vector>

#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoggedUser.h"
#include "Constants.h"

using std::vector;

/*
	usage: constructor
	in: reference to the requestHandlerFactory
	out: no
*/
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) :
	m_handlerFacotry(handlerFactory)
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
		case LOGIN_REQUEST:
			return this->login(requestInfo);
			break;

		case SIGN_UP_REQUEST:
			return this->signup(requestInfo);
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
	usage: the method tries to login into user's account, returns correspondly
	in: the request info
	out: if the login was succesful
*/
RequestResult LoginRequestHandler::login(const RequestInfo requestInfo) const
{
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	
	if (this->m_handlerFacotry.getLoginManager().login(loginRequest.username, loginRequest.password))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 1 })),
			this->m_handlerFacotry.createMenuRequestHandler(LoggedUser(loginRequest.username))
		};
	}
	
	return {
		JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 0 })),
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

	if (this->m_handlerFacotry.getLoginManager().signup(signUpRequest.username, signUpRequest.password, signUpRequest.email))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 1 })),
			this->m_handlerFacotry.createMenuRequestHandler(LoggedUser(signUpRequest.username))
		};
	}

	return {
		JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 0 })),
		this->m_handlerFacotry.createLoginRequestHandler()
	};
}
