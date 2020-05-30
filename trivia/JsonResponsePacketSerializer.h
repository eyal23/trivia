#pragma once

#include <iostream>
#include <vector>
#include <stdint.h>

using std::vector;

typedef struct LoginResponse
{
	unsigned int status = 1;
};

typedef struct SignupResponse
{
	unsigned int status = 1;
};

typedef struct ErrorResponse
{
	std::string message = "ERROR";
};


class JsonResponsePacketSerializer
{
public:
	static vector<uint8_t> serializeResponse(const ErrorResponse errorRes);
	static vector<uint8_t> serializeResponse(const LoginResponse loginRes);
	static vector<uint8_t> serializeResponse(const SignupResponse signRes);
};