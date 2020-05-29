#include <vector>

#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Constants.h"

using std::vector;

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
	vector<uint8_t> response;

	if (requestInfo.id == LOGIN_REQUEST)
	{
		LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		response = JsonResponsePacketSerializer::serializeResponse(LoginResponse({ 1 }));
	}
	else
	{
		SignUpRequest signUpRequest = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestInfo.buffer);
		response = JsonResponsePacketSerializer::serializeResponse(SignupResponse({ 1 }));
	}

	return { response, nullptr };
}
