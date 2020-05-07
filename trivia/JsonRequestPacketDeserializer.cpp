#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<uint8_t> buffer)
{
	return LoginRequest();
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(vector<uint8_t> buffer)
{
	return SignUpRequest();
}
