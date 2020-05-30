#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

class LoginRequestHandler : public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFacotry;
	LoginManager& m_loginManager;

public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(RequestInfo requestInfo) const override;
	RequestResult handleRequest(RequestInfo requestInfo) override;

private:
	RequestResult login(RequestInfo requestInfo);
	RequestResult signUp(RequestInfo requestInfo);
};