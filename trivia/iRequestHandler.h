#pragma once

#include <ctime>
#include <vector>

using std::vector;
using std::uint8_t;

enum RequestCode
{
	SIGN_UP,
	LOGIN,
};

typedef struct RequestInfo
{
	RequestCode id;
	time_t recivalTime;
	vector<uint8_t> buffer;
} RequestInfo;

class IRequestHandler;

typedef struct RequestResult
{
	vector<uint8_t> buffer;
	IRequestHandler* newHandler;
} RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo requestInfo) const = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
};

