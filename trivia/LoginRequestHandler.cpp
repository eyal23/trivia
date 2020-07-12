#include <vector>

#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "Constants.h"

using std::vector;


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
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "Request is non-relevant" })),
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
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ e.what() })),
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
	
	if (LoginManager::getInstance().login(loginRequest.username, loginRequest.password))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 1 })),
			RequestHandlerFactory::getInstance().createMenuRequestHandler(LoggedUser(loginRequest.username))
		};
	}
	
	return {
		JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 0 })),
		RequestHandlerFactory::getInstance().createLoginRequestHandler()
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

	if (LoginManager::getInstance().signup(signUpRequest.username, signUpRequest.password, signUpRequest.email))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 1 })),
			RequestHandlerFactory::getInstance().createMenuRequestHandler(LoggedUser(signUpRequest.username))
		};
	}

	return {
		JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 0 })),
		RequestHandlerFactory::getInstance().createLoginRequestHandler()
	};
}
