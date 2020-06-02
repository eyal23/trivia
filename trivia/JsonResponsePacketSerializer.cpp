#include <string>
#include <vector>

#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include "Constants.h"

using nlohmann::json;
using std::vector;

/**
* creates and sends the error massage respons.
*
* @param errorRes the error respons.
* @return bson vector of uint8 type respons for error.
*/
std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse errorRes)
{
	json j = { {"message", errorRes.message } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { ERROR_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/**
* creates and sends the log in respons.
*
* @param loginRes the log in respons.
* @return bson vector of uint8 type respons for login.
*/
std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LoginResponse loginRes)
{
	json j = { {"status", loginRes.status } };
	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { LOGIN_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/**
* creates and sends the sign up respons.
*
* @param signRes the sign up respons.
* @return bson vector of uint8 type respons for signup.
*/
std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const SignupResponse signRes)
{
	json j = { {"status", signRes.status } };
	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { SIGN_UP_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}
