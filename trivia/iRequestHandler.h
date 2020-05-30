#pragma once

#include <ctime>
#include <vector>

#include "Constants.h"

using std::vector;
using std::uint8_t;

typedef struct RequestInfo
{
	MessageCode id;
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
	virtual bool isRequestRelevant(const RequestInfo requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo requestInfo) = 0;
};

