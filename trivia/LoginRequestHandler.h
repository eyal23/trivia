#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFacotry;
	LoginManager& m_loginManager;

public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo requestInfo) const override;
	RequestResult handleRequest(const RequestInfo requestInfo) override;

private:
	RequestResult login(const RequestInfo requestInfo) const;
	RequestResult signup(const RequestInfo requestInfo) const;
};