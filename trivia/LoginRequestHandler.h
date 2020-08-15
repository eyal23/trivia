#pragma once

#include "IRequestHandler.h"



class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(const RequestInfo requestInfo) const override;
	RequestResult handleRequest(const RequestInfo requestInfo) override;

private:
	RequestResult login(const RequestInfo requestInfo) const;
	RequestResult signup(const RequestInfo requestInfo) const;
};