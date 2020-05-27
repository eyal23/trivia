#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include <string>

using nlohmann::json;

/**
* creates and sends the error massage respons.
*
* @param errorRes the error respons.
* @return bson vector of uint8 type respons for error.
*/
std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorRes)
{
	json j = json::parse(std::string("\"{message}\": ") + errorRes.message + std::string(", }"));
	std::vector<uint8_t> bson = json::to_bson(j);

	return bson;
}

/**
* creates and sends the log in respons.
*
* @param loginRes the log in respons.
* @return bson vector of uint8 type respons for login.
*/
std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes)
{
	json j = json::parse(std::string("\"{status}\": ") + std::to_string(loginRes.status) + std::string(", }"));
	std::vector<uint8_t> bson = json::to_bson(j);

	return bson;
}

/**
* creates and sends the sign up respons.
*
* @param signRes the sign up respons.
* @return bson vector of uint8 type respons for signup.
*/
std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(SignupResponse signRes)
{
	json j = json::parse(std::string("\"{status}\": ") + std::to_string(signRes.status) + std::string(", }"));
	std::vector<uint8_t> bson = json::to_bson(j);

	return bson;
}
