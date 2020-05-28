#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>



typedef struct LoginResponse
{
	unsigned int status = 1 ;
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
		std::vector<uint8_t> serializeResponse(ErrorResponse errorRes);
		std::vector<uint8_t> serializeResponse(LoginResponse loginRes);
		std::vector<uint8_t> serializeResponse(SignupResponse signRes);
};