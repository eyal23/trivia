#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"

using nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<uint8_t> buffer)
{
	json data = json::from_bson(buffer);

	return {
		data["username"],
		data["password"]
	};
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(vector<uint8_t> buffer)
{
	json data = json::from_bson(buffer);

	return {
		data["username"],
		data["password"],
		data["email"]
	};
}
