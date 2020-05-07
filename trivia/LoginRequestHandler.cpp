#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"

/*
	usage: the methods checks if a request is relevant
	in: the request info
	out: if the request is relevant
*/
bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	return requestInfo.id == LOGIN || requestInfo.id == SIGN_UP;
}

/*
	usage: the methods handles a request
	in: the request info
	out: the RequestResult object
*/
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
