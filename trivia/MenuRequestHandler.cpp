#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo)
{
	return RequestResult();
}
