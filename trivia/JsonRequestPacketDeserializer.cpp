#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"

using nlohmann::json;

/*
	usage: the method deserializes a json-buffer into a LoginRequest object
	in: the buffer
	out: the LoginRequest object
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<uint8_t> buffer)
{
	int* dataSize = (int*)(&buffer[1]);
	vector<uint8_t> data(buffer.begin() + 5, buffer.begin() + 5 + *dataSize);
	json jsonData = json::from_bson(data);

	return {
		jsonData["username"],
		jsonData["password"]
	};
}

/*
	usage: the method deserializes a json-buffer into a SignUpRequest object
	in: the buffer
	out: the SignUpRequest object
*/
SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(vector<uint8_t> buffer)
{
	int* dataSize = (int*)(&buffer[1]);
	vector<uint8_t> data(buffer.begin() + 5, buffer.begin() + 5 + *dataSize);
	json jsonData = json::from_bson(data);

	return {
		jsonData["username"],
		jsonData["password"],
		jsonData["email"]
	};
}
