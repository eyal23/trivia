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
* @return bson vector of uint8 type respons for sign up.
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

/**
* creates and sends the log out respons.
*
* @param logoutRes the log out respons.
* @return bson vector of uint8 type respons for logout.
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse logoutRes)
{
	json j = { {"status", logoutRes.status } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { 5 };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/**
* creates and sends the get rooms respons.
*
* @param getRoomsRes the get rooms respons.
* @return bson vector of uint8 type respons for the rooms.
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse getRoomsRes)
{
	json j = { {"status", getRoomsRes.status } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { 6 };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/**
* creates and sends the get all of the players in the room respons.
*
* @param getPlayersInRoomRes the number of players in a room respons.
* @return bson vector of uint8 type respons for getting the players that are in the rooms.
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse getPlayersInRoomRes)
{
	json j = { {"players", getPlayersInRoomRes.players } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { 6 };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/**
* creates and sends the join room respons.
*
* @param joinRoomRes the joining player into room respons.
* @return bson vector of uint8 type respons for the join player into a room.
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse joinRoomRes)
{
	json j = { {"status", joinRoomRes.status } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { 7 };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/**
* creates and sends the create room respons.
*
* @param createRoomRes the create room respons.
* @return bson vector of uint8 type respons for the create rooms.
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse createRoomRes)
{
	json j = { {"status", createRoomRes.status } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { 8 };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/**
* creates and sends the statistics respons.
*
* @param getStatisticsRes the statistics respons.
* @return bson vector of uint8 type respons for the statistics.
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetStatisticsResponse getStatisticsRes)
{
	json j = { {"statistics", getStatisticsRes.statistics } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { 6 };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}
