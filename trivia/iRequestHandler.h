#pragma once

#include <ctime>
#include <vector>

using std::vector;
using std::uint8_t;

typedef struct RequestInfo
{
	unsigned int id;
	time_t recivalTime;
	vector<uint8_t> buffer;
} RequestInfo;

typedef struct RequestResult
{
	vector<uint8_t> buffer;
	IRequestHandler* newHandler;
} RequestResult;

class IRequestHandler
{
	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);
};

