#pragma once

#include "IRequestHandler.h"

class MenuRequestHandler: public IRequestHandler
{
public:
	bool isRequestRelevant(const RequestInfo requestInfo) const override;
	RequestResult handleRequest(const RequestInfo requestInfo) override;
};

