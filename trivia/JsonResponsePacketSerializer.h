#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "Room.h"
#include "StatisticsManager.h"

using std::string;
using std::vector;
using std::map;

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	vector<RoomData> rooms;
} GetRoomsResponse;


typedef struct GetPlayersInRoomResponse
{
	unsigned int status;
	vector<string> players;
} GetPlayersInRoomResponse;

typedef struct GetStatisticsResponse
{
	unsigned int status;
	Statistics statitstics;
} GetStatisticsResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;

typedef struct CloseRoomResponse
{
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse
{
	unsigned int status;
} StartGameResponse;

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionsCount;
	unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
	unsigned int status;
} LeaveRoomResponse;

typedef struct LeaveGameResponse
{
	unsigned int status;
} LeaveGameResponse;

typedef struct GetQuestionResponse
{
	unsigned int status;
	string question;
	map<unsigned int, string> answers;
} GetQuestionResponse;

typedef struct SubmitAnswerResponse
{
	unsigned int status;
} SubmitAnswerResponse;

typedef struct PlayerResults
{
	string username;
	unsigned int correctAnswersCount;
	unsigned int wrongAnswersCount;
	float averageAnswerTime;
} PlayerResults;

typedef struct GetGameResultsResponse
{
	unsigned int status;
	vector<PlayerResults> results;
} GetGameResultsResponse;


class JsonResponsePacketSerializer
{
public:
	static vector<uint8_t> serializeResponse(const ErrorResponse errorRes);
	static vector<uint8_t> serializeResponse(const LoginResponse loginRes);
	static vector<uint8_t> serializeResponse(const SignupResponse signRes);
	static vector<uint8_t> serializeResponse(const LogoutResponse logoutRes);
	static vector<uint8_t> serializeResponse(const GetRoomsResponse getRoomsRes);
	static vector<uint8_t> serializeResponse(const GetPlayersInRoomResponse getPlayersInRoomRes);
	static vector<uint8_t> serializeResponse(const JoinRoomResponse joinRoomRes);
	static vector<uint8_t> serializeResponse(const CreateRoomResponse createRoomRes);
	static vector<uint8_t> serializeResponse(const GetStatisticsResponse getStatisticsRes);
	static vector<uint8_t> serializeResponse(const CloseRoomResponse closeRoomResponse);
	static vector<uint8_t> serializeResponse(const StartGameResponse startGameResponse);
	static vector<uint8_t> serializeResponse(const GetRoomStateResponse getRoomStateResponse);
	static vector<uint8_t> serializeResponse(const LeaveRoomResponse leaveRoomResponse);
	static vector<uint8_t> serializeResponse(const GetGameResultsResponse getGameResultsResponse);
	static vector<uint8_t> serializeResponse(const SubmitAnswerResponse submitAnswersResponse);
	static vector<uint8_t> serializeResponse(GetQuestionResponse getQuestionResponse);
	static vector<uint8_t> serializeResponse(const LeaveGameResponse leaveGameResponse);
};