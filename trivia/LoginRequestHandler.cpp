#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	return requestInfo.id == LOGIN || requestInfo.id == SIGN_UP;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
	if (requestInfo.id == LOGIN)
	{
		LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	}
	else
	{
		SignUpRequest signUpRequest = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestInfo.buffer);
	}
}
