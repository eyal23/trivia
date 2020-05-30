#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

/*
	usage: the method creates a login request handler
	in: no
	out: the login request handler
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

/*
	usage: the method gets the login manager
	in: no
	out: the login manager
*/
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
