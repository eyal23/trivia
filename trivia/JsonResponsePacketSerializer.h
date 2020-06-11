#pragma once

#include <iostream>
#include <vector>

#include "Room.h"
#include "StatisticsManager.h"

using std::string;
using std::vector;

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
	unsigned int hasGameBegun;
	vector<string> players;
	unsigned int questionsCount;
	unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
	unsigned int status;
} LeaveRoomResponse;


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
};