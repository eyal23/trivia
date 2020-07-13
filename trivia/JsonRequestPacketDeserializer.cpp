#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"

using nlohmann::json;

/*
	usage: the method deserializes a json-buffer into a LoginRequest object

	in: the buffer
	out: the LoginRequest object
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const vector<uint8_t> buffer)
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
SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const vector<uint8_t> buffer)
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

/**
* the method deserializes a json-buffer into a GetPlayersRequest object
*
*
* @param the buffer for the request
* @return the GetPlayersRequest object
*/
GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const vector<uint8_t> buffer)
{
	int* dataSize = (int*)(&buffer[1]);
	vector<uint8_t> data(buffer.begin() + 5, buffer.begin() + 5 + *dataSize);
	json jsonData = json::from_bson(data);

	return {
		jsonData["roomId"]

	};
}

/**
* the method deserializes a json-buffer into a JoinRoomRequest object
*
*
* @param the buffer for the request
* @return the JoinRoomRequest object
*/
JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const vector<uint8_t> buffer)
{
	int* dataSize = (int*)(&buffer[1]);
	vector<uint8_t> data(buffer.begin() + 5, buffer.begin() + 5 + *dataSize);
	json jsonData = json::from_bson(data);

	return {
		jsonData["RoomId"]
	};
}

/**
* the method deserializes a json-buffer into a CreateRoomRequest object
*
*
* @param the buffer for the request
* @return the CreateRoomRequest object
*/
CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const vector<uint8_t> buffer)
{
	int* dataSize = (int*)(&buffer[1]);
	vector<uint8_t> data(buffer.begin() + 5, buffer.begin() + 5 + *dataSize);
	json jsonData = json::from_bson(data);

	return {
		jsonData["RoomName"],
		jsonData["MaxUsers"],
		jsonData["QuestionCount"],
		jsonData["AnswerTimout"]
	};
}

/*
	usage: the method deserializes a json-buffer into a submit answer object
	in: the buffer
	out: the submit answer object
*/
SubmitAnswerRequest JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(const vector<uint8_t> buffer)
{
	int* dataSize = (int*)(&buffer[1]);
	vector<uint8_t> data(buffer.begin() + 5, buffer.begin() + 5 + *dataSize);
	json jsonData = json::from_bson(data);

	return {
		jsonData["AnswerId"],
		jsonData["AnswerTime"]
	};
}
