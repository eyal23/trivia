#pragma once

#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::uint8_t;

typedef struct LoginRequest
{
	string username;
	string password;
} LoginRequest;

typedef struct SignUpRequest
{
	string username;
	string password;
	string email;
} SingUpRequest;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(vector<uint8_t> buffer);
	static SignUpRequest deserializeSignUpRequest(vector<uint8_t> buffer);
};