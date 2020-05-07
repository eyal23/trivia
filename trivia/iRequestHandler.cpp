#include "IRequestHandler.h"

bool IRequestHandler::isRequestRelevant(RequestInfo)
{
	return false;
}

RequestResult IRequestHandler::handleRequest(RequestInfo)
{
	return RequestResult();
}
