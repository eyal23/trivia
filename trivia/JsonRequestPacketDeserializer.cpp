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
	json data = json::from_bson(buffer);

	return {
		data["username"],
		data["password"]
	};
}

/*
	usage: the method deserializes a json-buffer into a SignUpRequest object
	in: the buffer
	out: the SignUpRequest object
*/
SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(vector<uint8_t> buffer)
{
	json data = json::from_bson(buffer);

	return {
		data["username"],
		data["password"],
		data["email"]
	};
}
