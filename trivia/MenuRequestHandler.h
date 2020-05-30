#pragma once

#include "IRequestHandler.h"

class MenuRequestHandler: public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo requestInfo) const override;
	RequestResult handleRequest(RequestInfo requestInfo) override;
};

