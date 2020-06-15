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
	vector<uint8_t> message = { LOGOUT_RESPONSE };
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
	vector<string> rooms;

	for (int i = 0; i < getRoomsRes.rooms.size(); i++)
	{
		rooms.push_back(getRoomsRes.rooms[i].name);
	}

	json j = { {"Rooms", rooms } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { GET_ROOMS_RESPONSE };
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
	json j = { {"PlayersInRoom", getPlayersInRoomRes.players } };
	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { GET_PLAYERS_IN_ROOM_RESPONSE };
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
	vector<uint8_t> message = { JOIN_ROOM_RESPONSE };
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
	vector<uint8_t> message = { CREATE_ROOM_RESPONSE };
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
	json j = { 
		{ "UserStatistics", { 
				{ "AverageAnswerTime", getStatisticsRes.statitstics.averageAnswerTime },
				{ "NumberOfCorrectAnswers", getStatisticsRes.statitstics.numberOfCorrectAnswers },
				{ "NumberOfTotalAnswers", getStatisticsRes.statitstics.numberOfTotalAnswers },
				{ "NumberOfPlayerGames", getStatisticsRes.statitstics.numberOfPlayerGames } }
		},
		{ "HighScores", json::array() }
	};

	for (int i = 0; i < 5; i++)
	{
		j["HighScores"].push_back(getStatisticsRes.statitstics.topScores[i]);
	}

	vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { GET_STATISTICS_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/*
	usage: the method serializes a close room response
	in: the close room response
	out: the serialized response
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse closeRoomResponse)
{
	json j = { {"status", closeRoomResponse.status } };
	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { CLOSE_ROOM_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/*
	usage: the method serializes a start game response
	in: the start game response
	out: the serialized response
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const StartGameResponse startGameResponse)
{
	json j = { {"status", startGameResponse.status } };
	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { START_GAME_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/*
	usage: the method serializes a get room state response
	in: the get room state response
	out: the serialized response
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse getRoomStateResponse)
{
	json j = { 
		{"status", getRoomStateResponse.status },
		{"HasGameBegun", getRoomStateResponse.hasGameBegun },
		{"Players", getRoomStateResponse.players },
		{"QuestionsCount", getRoomStateResponse.questionsCount },
		{"AnswerTimeout", getRoomStateResponse.answerTimeout },
	};

	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { GET_ROOM_STATE_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

/*
	usage: the method serializes a leave room response
	in: the leave room response
	out: the serialized response
*/
vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse leaveRoomResponse)
{
	json j = { {"status", leaveRoomResponse.status } };
	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { LEAVE_ROOM_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetGameResultsResponse getGameResultsResponse)
{
	json j = { 
		{"status", getGameResultsResponse.status },
		{"Results", json::array()}
	};

	for (int i = 0; i < getGameResultsResponse.results.size(); i++)
	{
		j["Results"].push_back(json({
			{ "Username", getGameResultsResponse.results[i].username },
			{ "CorrectAnswersCount", getGameResultsResponse.results[i].correctAnswersCount },
			{ "WrongAnswersCount", getGameResultsResponse.results[i].wrongAnswersCount },
			{ "AverageAnswerTime", getGameResultsResponse.results[i].averageAnswerTime }
			})
		);
	}

	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { GET_GAME_RESULT_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const SubmitAnswerResponse submitAnswersResponse)
{
	json j = { {"status", submitAnswersResponse.status } };
	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { SUBMIT_ANSWER_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse getQuestionResponse)
{
	json j = { 
		{"status", getQuestionResponse.status },
		{ "Question", getQuestionResponse.question },
		{ "Asnwers", {
			{ 0, getQuestionResponse.answers[0] },
			{ 1, getQuestionResponse.answers[1] },
			{ 2, getQuestionResponse.answers[2] },
			{ 3, getQuestionResponse.answers[3] }
		}}
	};
	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { GET_QUESTION_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}

vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LeaveGameResponse leaveGameResponse)
{
	json j = { {"status", leaveGameResponse.status } };
	std::vector<uint8_t> bson = json::to_bson(j);

	int dataSize = bson.size();
	vector<uint8_t> message = { LEAVE_GAME_RESPONSE };
	message.resize(5);

	memcpy((uint8_t*)(message.data() + 1), (uint8_t*)&dataSize, 4);

	message.insert(message.end(), bson.begin(), bson.end());

	return message;
}
